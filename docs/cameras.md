
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

### The lens camera

The lens is an optical device which focuses or disperses the light beam. For our purposes we will be interested in focusing lenses only. 

Normally the lenses are axially symmetric. The symmetry axis of the lens is called  {\it principal axis}. The key property of the lens is that it refracts the rays coming from a point so that they all meet in a single point on the opposite side of the lens. The rays parallel to the ***principal axis*** always pass through a special point called ***focus*** **F**. The rays through the lens' center pass intact. See Figure 5.

<p align="center">
  <img width="80%" src="/images/lens.png">  
  <p align="center">Figure 5: The refraction of rays through a thin focusing lens. Rays emitted by a point on the distance d from the lens meet at a single point, which is at a distance l from the lens.</p>
</p>

From Figure 5 it is easy to derive the ***lens formula***:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?\frac{1}{f}&space;&plus;&space;\frac{1}{d}&space;=&space;\frac{1}{l}." />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (3)
</p>

This formula implies that if we place our sensor at distance the *l* determined from (3), all the points which are at the same distance *d* from the lens will be nicely projected on the sensor. Adjusting the position of the sensor to the lens will enable us to take sharp pictures of objects at different distances. 

The relations between the distances from the principal axis read:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?h'&space;=&space;l\frac{h}{d}\equiv&space;\frac{fh}{d-f}" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (4)
</p>

**What happens to the points which are at a slightly different distance?** or, equivalently,  **What happens if we place the sensor in a slightly different location?**


<p align="center">
  <img width="80%" src="/images/lens_confusion_circle.png">  
  <p align="center">Figure 6: The distorted image of the point caused by incorrect placement of the sensor. Note, the center of the circle of confusion is at a slightly different distance from the principal axis than the image of the point.</p>
</p>


Figure 6 illustrates the process. The light cone focusing in the image of the point will be cut and, instead of a point we will have an illuminated disk - the ***circle of confusion***. The photos taken by such a wrongly placed sensor will be blurred or *not in focus*. 

The distance between the center of the circle of confusion and the principle axis will be different from that of the point's image:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?h''&space;=&space;h'\frac{l'}{l}&space;\equiv&space;\frac{hl'}{d}" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (5)
</p>

where *h''* is the distance between the center of the circle of confusion and the principal axis, *l* is the ideal distance between the sensor and the lens, *h* is the distance between the point and the principal axis and *h'* is the distance between the image of the point on the ideally located sensor and the principal axis. See Figure 6.

It is clear from the diagram that depending on the diameter of the lens, the slight errors in the placement of the sensor can lead to a significant circle of confusion and, hence, blurring. Besides, the real world objects are not flat and we want to be able to make sharp photos of acceptable  sizes. We can control  the radius of the lens by placing a black screen with a small aperture right next to the lens (see Figure 7) 

<p align="center">
  <img width="80%" src="/images/lens_confusion_circle_aperture.png">  
  <p align="center">Figure 7: The aperture disc reduces the circle of confusion.</p>
</p>

Assuming that the sensor is placed at distance *l' ≠ l* from the lens, where *l* is the correct distance determined from (3) and that the diameter of the aperture is *D*, it is easy to derive the diameter of the circle of confusion *c*:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?c&space;=&space;D\left(1-\frac{l'}{l}\right)," />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (6)
</p>
or, if we substitute the value of *l*:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?c=D\left(1&space;-l'&space;\left(\frac{1}{f}&space;-&space;\frac{1}{d}\right&space;)\right&space;)" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (7)
</p>

Surprisingly,  the diameter does not depend on the distance of the point from the principle axis rather depends only on the distance of the point from the lens( *l* depends on the *d*).  

Note, that placing the ***aperture disk*** between the object and the lens does not change the position of the image of the point. The ideally located sensor will feel the presence of the aperture disk only by the reduction of the reaching light amount. 

By sufficiently reducing the aperture diameter we can make the circle of confusion of any point smaller than the half of the sensor's pixel. Further reduction will not contribute to the sharpness (because we have reached the sensor's sharpness limit) but will rather  make the image only dimmer.

Obviously, the smaller the aperture diameter the deeper objects we can have in focus. 

Note, since the rays passing through the lens' center do not refract, in the limit of infinitely small aperture the presence of the lens can be neglected and this will turn into the pinhole camera described above. 

### Fixed focus cameras

Since in the future posts we will mostly play with web cameras and the majority of webcams are so-called fixed-focus cameras, let us dive a little deeper into this particular corner case.

First of all, let us rewrite the formula (3) as follows:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?l=\frac{df}{d-f}\equiv\frac{f}{1&space;-&space;f/d}." />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (8)
</p>

Notice, that for sufficiently far objects *d >> f* the denominator in (8) goes to one and, therefore, the ideal location of the sensor will be close to the focus. The typical focal length of the modern cameras bounces around *1-10 mm* so this condition is satisfied with high precision for our everyday objects and distances (*~ 1m*). We can assume that with high precision that the sensors of the fixed-focus webcams are placed in the focus of the lens. 

Now, if we substitute *l'=f* in (7) two first terms will cancel each other and we will arrive to the following formula:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?c=\frac{Df}{d}" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (9)
</p>

It is clear from the formula that the larger is *d* the smaller is the circle of confusion *c*. So, for the fixed focal length *f* and aperture diameter *D* all points which are farther than *d<sub>0</sub>* from the lens

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?d_0&space;=&space;\frac{Df}{c}&space;\label{hyperfocal}" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (10)
</p>
will have a circle of confusion less than *c*. This is called ***hyperfocal distance***. If for *c* we take half the  size of our sensing pixel, all objects which are farther than (10) from the lens will be as sharp as our sensor can possibly make. 

Finally, the distance of the image of the point from the principal axis, according to (5) will read:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?h''&space;=&space;\frac{hf}{d}" />  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (11)
</p>

Comparing this to (1) shows that we can use formulae  (2) for the fixed focus cameras.
