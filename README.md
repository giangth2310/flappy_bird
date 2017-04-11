This is my project: flappy bird written in C++ with SDL, SDL_image, SDL\_ttf and SDL\_mixer

Base on my 0.1 project where I tested logic game (you can see it [here](https://github.com/giangth2310/flappy_bird_0.1)), I added animation and image to this version to make it look like the original version of Nguyễn Hà Đông.

Something I think you don't understand when you read my code is **background_1** and **background\_2**
So, look at the following image 

![Endless moving background - flappy bird project](http://imgur.com/97Q28IH.png)

When the **background_1** moves out of the main background, **background\_1** := **background\_2** and **background\_2** is initiated again. That is called fake scrolling. Similar to the ground and block.

When a up-block and a down-block move out of the screen, I add new up-block **(UpBlock\_2**) and down-block (**DownBlock\_2**) and delete the older one. **UpBlock_1** (**DownBlock\_1**) always point to the up-block (down-block) in the screen. 

&copy; 2017, giangth2310