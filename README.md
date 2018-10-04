# camera
#basic idea of the project: to caliberate the cameras
1. several PMTs are chosen from the pictures and their pixel position are measured by hand.
2. the camera is modeled by 11 parameters: two for position of camera(theta and phi, r fixed), 3 for the orientation of camera, 3 for the magnifica of lens in x direction and 3 for the y direction.
3. Using the model of camera, by calculating the light path, the pixel positions of chosen PMTs are matched to the 3D coordinates of several pmts in the database
4. according to coordinates of the PMTs in the database, based on the behaviour of fish eye lens and refraction of the AV, a calculated picture can be created with the guessed 11 parameters. The calculated pixel position of the chosen PMTs can be also obtained.
5. Then for the chosen PMTs, the difference of calculated pixel and the measure pixel is minimized by a fit program, this is done by let the computer vary the 11 parameter.
6. Then the fit result will give the best 11 parameters. Using the result, a plot of calculated pmts can be drawn on top of the original picture.

#Comment on how each file works
1. camera P will be used as an example. Files in script/p/ will be commented. Other files for camera 1, 2,3 will work in similar way.
