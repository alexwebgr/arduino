require 'csv'

filename = 'temperature_data.csv'

temperature_readings = []

CSV.foreach(filename, headers: true) do |row|
  temperature_readings << row['temperature_c'].to_f
end

puts "=" * 50
puts "Temperature Data Analysis"
puts "=" * 50
puts "Total readings: #{temperature_readings.length}"
puts ""
if temperature_readings.length > 0
  puts "Temperature (°C):"
  puts "  Min:     #{temperature_readings.min.round(1)}"
  puts "  Max:     #{temperature_readings.max.round(1)}"
  puts "  Average: #{(temperature_readings.sum / temperature_readings.length).round(1)}"
end
puts "=" * 50
