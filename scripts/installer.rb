file = ARGV[0]
puts "Flashing #{file}..."
system("arduino-cli compile --fqbn arduino:avr:uno #{file}")
system("arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno #{file}")
