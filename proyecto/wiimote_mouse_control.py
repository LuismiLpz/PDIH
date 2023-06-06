#!/usr/bin/python
# -*- coding: iso-8859-15 -*-
#sudo wminput -w -c '/home/luismilpz/Desktop/wiimote/map'
import cwiid
import time
from Xlib import X, display
#Sensibilidad de los acelerómetros
SENSITIVITY = 0.1
#Velocidades límite de los acelerometros
MAX_SPEED = 10
MIN_SPEED = -10

#Delay entre inputs

UPDATE_DELAY = 0.01

#Tamaño de pantalla

SCREEN_WIDTH =1920
SCREEN_HEIGHT = 945

def move_mouse(dx, dy):
	d = display.Display()
	s = d.screen()
	root = s.root
	root.warp_pointer(int(dx), int(dy))
	d.sync()

def main():
	print("Press the 1+2 buttons on your Wiimote to connect...")
	wiimote = None
	while not wiimote:
		try:
			wiimote = cwiid.Wiimote()
		except RuntimeError:
			pass

	print("Wiimote connected")
	wiimote.rpt_mode = cwiid.RPT_BTN | cwiid.RPT_ACC #Controlan botones y acelerómetros

	try:
		while True:
			buttons = wiimote.state['buttons']
			acc = wiimote.state['acc']

			if buttons & cwiid.BTN_A:
				print("Button A pressed")
			if buttons & cwiid.BTN_B:
				print("Button B pressed")

			dx = (acc[0]*125)*SENSITIVITY
			dy = (acc[1]*125)*SENSITIVITY

			current_x = display.Display().screen().root.query_pointer().root_x
			current_y = display.Display().screen().root.query_pointer().root_y
			new_x = current_x + dx
			new_y = current_y + dy
	
			new_x = max(0, min(new_x, SCREEN_WIDTH))
			new_y = max(0, min(new_y, SCREEN_HEIGHT))

			move_mouse(new_x, new_y)

			time.sleep(UPDATE_DELAY)

	except KeyboardInterrupt:
		print("\nExiting...")
if __name__ == "__main__":
	main()








