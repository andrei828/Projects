import pygame, sys
import pygame.camera
pygame.init()

screen = pygame.display.set_mode((800, 300))

#background
red = 255, 0, 0

# set icon 
ball = pygame.image.load("ball.gif")
pygame.display.set_icon(ball)

#set caption
pygame.display.set_caption("This is the title")
pygame.camera.init()
print(pygame.camera.list_cameras())

while 1:
	# exit program
	for event in pygame.event.get():
		if event.type == pygame.QUIT: 
			sys.exit()

	screen.fill(red)
	pygame.display.update()


