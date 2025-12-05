require 'serialport'

class ActivityValidator
  PORT_NAME = "/dev/ttyACM0"
  BAUD_RATE = 9600
  DATA_BITS = 8
  STOP_BITS = 1
  PARITY = SerialPort::NONE

  def initialize
    @tests = []
  end

  def run
    flash_firmware
    # Initialize the connection.
    serial_port

    # Clear messages sent during setup
    flush_read_buffer

    run_test_suite
    serial_port.close
  end

  private

  def flash_firmware
    return unless ARGV.include? "--install"

    puts "Flashing sound_sensor..."
    system("arduino-cli compile --fqbn arduino:avr:uno sound_sensor")
    system("arduino-cli upload -p #{PORT_NAME} --fqbn arduino:avr:uno sound_sensor")
    sleep(2) # Wait after upload
  end

  def serial_port
    @serial_port ||= begin
      serial_port = SerialPort.new(PORT_NAME, BAUD_RATE, DATA_BITS, STOP_BITS, PARITY)
      serial_port.read_timeout = 2000 # Prevent hanging forever
      sleep(2) # CRITICAL: Wait for Arduino to reboot after serial connect
      serial_port
    end
  end

  # I used a non-blocking read loop to manually drain the OS serial buffer.
  # It actively pulls bytes until the IO::WaitReadable exception is raised,
  # ensuring that no stale data from previous tests contaminates the current test assertion.
  def flush_read_buffer
    while (serial_port.read_nonblock(1) rescue nil); end
  end

  def run_test(input_force, expected_state)
    print "TESTING: Injecting Force #{input_force}... "

    # 1. Ensure line is clear
    flush_read_buffer

    # 2. Send Command
    serial_port.write("#{input_force}\n")

    # 3. Read Response
    # expect a \n to proceed
    # gets can return nil if timeout, so we handle that safely
    response = serial_port.gets&.chomp || "TIMEOUT"

    if response.include?(expected_state)
      puts "PASS (#{response})"
      true
    else
      puts "FAIL (Expected #{expected_state}, got #{response})"
      false
    end
  end

  def run_test_suite
    return unless ARGV.include? "--run_tests"

    puts "--- HIL Test Suite Initialized ---"
    puts "Connecting to Device Under Test (DUT)..."

    test_state_below_threshold
    test_state_soft
    test_state_med
    test_state_hi

    puts "----------------------------------------"
    puts "Test Suite Completed. #{(@tests - [false]).length}/#{@tests.length} passed."
  end

  def test_state_below_threshold
    @tests << run_test(99, "99")
  end

  def test_state_soft
    @tests << run_test(100, "100 PIN_SOFT")
  end

  def test_state_med
    @tests << run_test(250, "250 PIN_SOFT + PIN_MED")
  end

  def test_state_hi
    @tests << run_test(320, "320 PIN_SOFT + PIN_MED + PIN_HI")
  end
end

ActivityValidator.new.run
