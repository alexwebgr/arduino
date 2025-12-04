require 'serialport'

PORT = '/dev/ttyACM0'
BAUD_RATE = 9600
DATA_BITS = 8
STOP_BITS = 1
PARITY = SerialPort::NONE

START_MARKER = '---START_MARKER---'
END_MARKER = '---END_MARKER---'

# Flash firmware first with arduino-cli
puts "Flashing factory test firmware..."

system("arduino-cli compile --fqbn arduino:avr:uno temperature_logger_lm_35_factory_test")
system("arduino-cli upload -p #{PORT} --fqbn arduino:avr:uno temperature_logger_lm_35_factory_test")

sleep(2)  # Wait for Arduino to init

puts "Running factory tests..."
serial_port = SerialPort.new(PORT, BAUD_RATE, DATA_BITS, STOP_BITS, PARITY)

# Wait for start marker
loop do
  start_line = serial_port.gets&.chomp
  break if start_line&.include?(START_MARKER)
end

# Capture output
output = []
while (line = serial_port.gets&.chomp)
  break if line.include?(END_MARKER)

  output << line
  puts line
end
