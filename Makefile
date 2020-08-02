
phony: clean bin

bin:
	arduino-cli compile --fqbn arduino:avr:uno 

clean:
	rm -rf *.hex *.elf

upload:
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno 