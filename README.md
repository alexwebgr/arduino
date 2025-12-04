# Adventures in Arduino land

A series of arduino sketches along with some integrations and testing in ruby and arduino.

## Temperature Logging with LM35
A simpler logger for the [LM35](https://www.ti.com/lit/ds/symlink/lm35.pdf?ts=1764811951832) analog sensor that includes 

* the actual sketch [temperature_logger_lm_35.ino](temperature_logger_lm_35/temperature_logger_lm_35.ino)
* a factory test sketch [temperature_logger_lm_35_factory_test.ino](temperature_logger_lm_35_factory_test/temperature_logger_lm_35_factory_test.ino)
* a ruby script that compile uploads and runs the test suite [temperature_logger_lm_35_factory_test.rb](tests/temperature_logger_lm_35_factory_test.rb)
* a ruby script that will connect and collect the temperature readings in a .csv file [collect_data_lm_35.rb](scripts/collect_data_lm_35.rb)
* a ruby script that will summarize the findings [analyze_data_lm_35.rb](scripts/analyze_data_lm_35.rb)

<img src="https://github.com/user-attachments/assets/7a809165-2f97-42b8-87bb-033288ede416" width="300" alt="LM35">

## Running locally
Developed on Ubuntu 24.

You will need ruby installed matching the version in `.ruby-version` and [arduino-cli](https://docs.arduino.cc/arduino-cli/installation/?_gl=1*1y47acn*_up*MQ..*_ga*MjEzNjEwNzcxMy4xNzY0ODU3MzM0*_ga_NEXN8H46L5*czE3NjQ4NTczMzMkbzEkZzAkdDE3NjQ4NTczMzMkajYwJGwwJGgxNzU3MjQ0MzUy)

Then `bundle install` for the ruby dependencies.

Having [arduino ide](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/) installed is helpful.
