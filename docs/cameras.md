
### The Pinhole Camera

Let us assume that we have a light emitting point in 3D space and a 2D sensor. If we place the point in front of the sensor the emitted rays  will fully cover the  sensor's surface and we will not receive any valuable information other than the acknowledgment of a bright point next to our sensor.  Figure 1.

<p align="center">
  <img width="60%" src="/images/point.png">  
  <p align="center">Figure 1: The light from the point covers the whole sensor</p>
</p>

To get a more detailed picture, let us place a black screen with a tiny hole between the sensor and the point. If the hole is small enough only the rays which connect the point to the hole will pass the screen and we will project our point in space on a single point on our sensor.  Figure 2 illustrates the described process. 

<p align="center">
  <img width="80%" src="/images/pinhole_point.png"> 
  <p align="center">Figure 2: Only a single point on the sensor is illuminated by the light emitted from the point</p>  
</p>

The axis orthogonal to the screen (and the sensor) and passing through the hole is called ***principal axis***. The distance from the screen to the sensor is called ***focal length***. 

It is clear from Figure 2 that objects in general will appear upside down on the sensor. 

Using similarity relations between triangles it is easy to derive the following relation between the actual distance of the point from the principal axis and that of its image:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?h'=h\frac{f}{d}" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (1)
</p>

Let us rewrite this formula in the coordinate language. Let us introduce  the 3D world coordinate system  with axes (X,Y,Z) and 2D image coordinate system with axes (x,y) as shown in Figure 3.

<p align="center">
  <img width="80%" src="/images/pinhole_coords.png">  
  <p align="center" valign="center">Figure 3: World and image coordinate systems</p>
</p>

If we first place the origin of the image coordinate system in the point where the principal axis intersects the sensor plane the (1) leads to:
<p align="center">
<img src="https://latex.codecogs.com/gif.latex?%5Cleft%5C%7B%5Cbegin%7Barray%7D%7Bc%7D%20x%20%3D%20f%20%5Cfrac%7BX%7D%7BZ%7D%20%5C%5C%20y%20%3D%20f%20%5Cfrac%7BY%7D%7BZ%7D%20%5Cend%7Barray%7D%5Cright." />  
</p>

In the digital world, however, the origin of the coordinate system on the image is placed in the top left corner of the image(sensor) so all points (0,0,Z) are projected to the principal point (c<sub>x</sub>, c<sub>y</sub>).  To include this, we rewrite the formulae as follows:  
<p align="center">
<img src="https://latex.codecogs.com/gif.latex?%5Cleft%5C%7B%5Cbegin%7Barray%7D%7Bc%7D%20x%20%3D%20f%20%5Cfrac%7BX%7D%7BZ%7D%20&plus;%20c_x%5C%5C%20y%20%3D%20f%20%5Cfrac%7BY%7D%7BZ%7D%20&plus;%20c_y%20%5Cend%7Barray%7D%5Cright." />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (2)
</p>

This is the so-called ***projection formula*** for pinhole camera. In the upcoming posts we will linearize it  and represent in a matrix form. 

In the end of this section, let us notice that in order to project a point on a point the described method requires the hole on the screen to be as small as possible, ideally - a point.  In the real world, however, it is impossible to make an infinitely small hole. When it has finite size the image of the point turns into a disk - the ***circle of confusion***. See Figure 4.

<p align="center">
  <img width="80%" src="/images/confusion_circle.png">  
  <p align="center">Figure 4: The finite size of the hole causes point to turn into a circle of confusion.</p>
</p>

Obviously, the wider the hole the the bigger the  circle of confusion. Also, the closer the point to the screen, the wider the confusion circle. 

**An interesting fact: the stars are so far from us, that the rays coming from them are almost parallel and, therefore, the diameter of the confusion circle is equal to the diameter of the hole on the screen.**

However, due to a number of reasons we cannot make the hole very small.

First of all a smaller hole means less light reaching the sensor and, as a result,  dimmer pictures. On the other hand, if, for example,  we use a digital sensor, and  make the hole so small that in the distance range interesting for us the confusion circle is not bigger than a pixel on the sensor; no matter how small we make the hole, our picture will not get any sharper, it will rather get dimmer and dimmer until vanishes in the noise of the device.

The second and, probably not very actual, reason is that even if we could amplify the light coming from the objects or make the sensor's pixels infinitely sensitive there is another effect which emerges when the radius of the hole becomes comparable to the wavelength of the optical light - the optical diffraction. This is, perhaps, the theoretical limitation of the pinhole camera model. In practice, however the boundaries are much closer due to the limitations of the sensors. 
