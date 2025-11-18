push: push.c
	gcc $< -o $@ -L/opt/homebrew/Cellar/openmotif/2.3.8_3/lib -L/opt/homebrew/Cellar/libxt/1.3.1/lib -L/opt/homebrew/Cellar/libx11/1.8.12/lib -lXm -lXt -lX11 -I/opt/homebrew/Cellar/openmotif/2.3.8_3/include -I/opt/homebrew/Cellar/libx11/1.8.12/include -I/opt/homebrew/Cellar/libxt/1.3.1/include -I/opt/homebrew/Cellar/xorgproto/2024.1/include -I/opt/homebrew/Cellar/libsm/1.2.6/include -I/opt/homebrew/Cellar/libice/1.1.2/include -I/opt/homebrew/Cellar/libxext/1.3.6/include -I/opt/homebrew/Cellar/libxp/1.0.4/include -I/opt/homebrew/Cellar/libxau/1.0.12/include


clean:
	rm push

.PHONY: clean