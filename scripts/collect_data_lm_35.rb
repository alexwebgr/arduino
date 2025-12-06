require 'serialport'
require 'time'

# Configuration
PORT_NAME = '/dev/ttyACM0'
BAUD_RATE = 9600
DATA_BITS = 8
STOP_BITS = 1
PARITY = SerialPort::NONE

OUTPUT_FILE = 'temperature_data.csv'

if ARGV[0] == "--install"
  puts "Flashing temperature_logger_lm_35..."
  system("arduino-cli compile --fqbn arduino:avr:uno temperature_logger_lm_35")
  system("arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno temperature_logger_lm_35")
end

begin
  # Open serial connection
  serial_port = SerialPort.new(PORT_NAME, BAUD_RATE, DATA_BITS, STOP_BITS, PARITY)

  # Give Arduino time to reset after connection
  sleep(2)

  puts "Connected! Logging data to #{OUTPUT_FILE}"
  puts "Press Ctrl+C to stop"

  # Open output file
  File.open(OUTPUT_FILE, 'a:UTF-8') do |file|
    # Write header if file is empty
    if File.zero?(OUTPUT_FILE)
      file.puts "timestamp,temperature_c"
    end

    # ignore the first line because it contains previous reading
    serial_port.gets

    loop do
      # Read line from Arduino
      line = serial_port.gets&.chomp

      next if line.nil? || line.empty?

      if line.include?("ERROR")
        puts line
        next
      end

      timestamp = Time.now.strftime("%Y-%m-%d %H:%M:%S")
      file.puts "#{timestamp},#{line}"
      file.flush  # Ensure data is written immediately
      print '.'
    end
  end

rescue Interrupt
  puts "Stopping data collection..."
  puts "Data saved to #{OUTPUT_FILE}"

rescue StandardError => e
  puts "ERROR: #{e.message}"
  puts e.backtrace

ensure
  serial_port&.close
  puts "Connection closed."
end
