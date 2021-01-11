all:
	
version:
	pacman --version
search:
	pacman -Ss $(GPACMAN_PACKAGE_SEARCH) | grep -ie "i686"
