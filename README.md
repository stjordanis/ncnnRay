
<h1 align="center">    
  <img src="https://github.com/QuantScientist/ncnnRay/blob/main/assets/logo.png?raw=true" width="25%"></a>  
</h1>

<h1 align="center">ncnnRay++: A CMake integration of rayib and the Tencent ncnn C++ AI platform into HTML / WASM.</h1>
      
<p align="center">
  <a href="#about">About</a> •
  <a href="#credits">Credits</a> •
  <a href="#installation">Installation</a> •  
  <a href="#fexamples">Examples</a> •  
  <a href="#author">Author</a> •  
  <a href="#license">License</a>
</p>


---

# About

<h1 align="center">    
  <img src="https://github.com/QuantScientist/ncnnRay/blob/main/assets/manga.png.exp.png?raw=true" width="55%"></a>  
</h1>


  
**ncnnRay++** is a CMake based **integration** of **_raylib_** and the very popular Tencent ncnn Deep Learning library. 
ncnn is written in C++ designed (but not only) for edge computing devices. ncnnRay solely uses the ncnn 
project as the universal neural network inference framework.
 
**There is no OpenCV dependency for reading and writing images / videos or anything else**. Everything is self-contained 
using stb_image . The library includes conversion utils between ray Image, `ncnn::Mat` and PNG lib, all of which are interchangeable.
For more details, refer to: 
- https://github.com/QuantScientist/ncnnRay/blob/master/include/utils/vision_utils.hpp     
 
**Why??++** The goal is to integrate both libraries into HTML using Webassembly. ray is already natively supported on WASM. 
This would open the door to thousands of opportunities!.  

# Available AI Models (Tencent ncnn in C++)
 
 <div align='left'>
 <table>
   <th>Image</th>
   <th>Model name</th>   
   <th>Credit C++ implementation<br/></th>
   <th>NCNN_DEVICE<br/></th>
   <th>Paper <br/></th>         
   <tr>          
     <td><img src='https://github.com/QuantScientist/ncnnRay/blob/main/assets/faces.png.exp.png?raw=true' width="600px"></td>
     <td>LFFD</td>              
     <td> <a href="https://github.com/SyGoing/LFFD-with-ncnn">Credit ncnn C++</a>
     and <a href="https://github.com/YonghaoHe/A-Light-and-Fast-Face-Detector-for-Edge-Devices">LFFD: A Light and Fast Face Detector for Edge Devices</a> 
     </td>         
     <td> CPU only </td>         
     <td> <a href="https://arxiv.org/abs/1904.10633">LFFD: A Light and Fast Face Detector for Edge Devices</a>              
      </td>              
   </tr>                 
 </table>
 </div>


# GPU or CPU?  
If you want to test on a CPU you will have to edit the CMakeLists file. ncnn uses the Vulkan SDK for all its GPU operations. 

GPU (Vulkan) mode:
```cmake
set(NCNN_DEVICE "VULKAN")
```
CPU mode: 
```cmake
set(NCNN_DEVICE "cpu")
```
**Note**: Tested only on **GPU with CUDA 10.2 and a CPU on a Windows 10 machine**. 

## RayLib 
rayLib is an amazing library which has been widely adopted by the gaming community. 
Read more about the raylib game framework here: https://www.raylib.com/
Or look up projects using it here:
https://www.google.com/search?q=raylib+site:github.com   

## Tencent ncnn 
Written in C++, ncnn has a community that is growing by the day. It compiles on almost every platform and is 
mainly targeted at egde devices.    
  
<p align="right">
<sub>(Preview)</sub>
</p>

## A simple example 
The folowing example create a ray window, allocates a `ncnn::Mat` on the GPU and draws the value  into a ray window. 
 
```cpp
#include "../include/utils/vision_utils.hpp"
int main(int argc, char** argv) {
    VisionUtils vu=VisionUtils(); 

    //RGB
    Image image = LoadImage("parrots.png");   
    ncnn::Mat inmat =vu.rayImageToNcnn(image);
    std::cout<<"Total:" << inmat.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmat) <<std::endl;;
    Image saveImage=vu.ncnnToRayImage(inmat);
    ExportImage(saveImage, "parrots-ncnn-rgb.png");
    
    //RGBA
    Image imageRGBA = LoadImage("windmill.png");   
    ncnn::Mat inmatimageRGBA =vu.rayImageToNcnn(imageRGBA);
    std::cout<<"Total:" << inmatimageRGBA.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmatimageRGBA) <<std::endl;;
    Image saveImageimageRGBA=vu.ncnnToRayImage(inmatimageRGBA);
    ExportImage(saveImageimageRGBA, "big-cat-ncnn-rgba.png");    

    return 0;
```

## Credits + Third party libraries I used

* RayLib UI + raylib https://github.com/raysan5/raylib which is licensed under 
an unmodified zlib/libpng license (View raylib.h for details) Copyright (c) 2014 Ramon Santamaria (@raysan5) 

* ncnn 
## Progress / features 

|                            | 🔰 ncnnRay++ CMake  | |
| -------------------------- | :----------------: | :-------------:|
| `ncnn:Mat` CPU tensor to stb Image        |         ✔️                 
| `ncnn:Mat` GPU tensors to stb image       |         ✔️                 
| stb image to CPU `ncnn:Mat`        |         ✔️
| Save `ncnn:Mat` as stb PNG image on disk         |         ✔️


# Examples

## A Simple example, mainly for testing the integration. Read an Image, allocate an `ncnn:Mat` tensor on the CPU.
- https://github.com/QuantScientist/ncnnRay/blob/main/src/ncnnRay_read_image.cpp

## LFFD: A Light and Fast Face Detector for Edge Devices
- https://github.com/QuantScientist/ncnnRay/blob/main/src/ncnnRay_lfd.cpp
```
@inproceedings{LFFD,
title={LFFD: A Light and Fast Face Detector for Edge Devices},
author={He, Yonghao and Xu, Dezhong and Wu, Lifang and Jian, Meng and Xiang, Shiming and Pan, Chunhong},
booktitle={arXiv:1904.10633},
year={2019}
}
```


## Requirements:
* tested only on Windows 10 and Microsoft Visual C++ 2019 16.4
* NVIDIA CUDA 10.2 + Vulkan SDK . I did not test with any other CUDA version. 
* ncnn  (downloaded automatically)  
* Tested on 64 bit only device.  
* CMake 3.18   
* rayLib GUI (downloaded automatically).

# Building using CMake

## ncnn 
**CMake** should take care of everything for you!   
````bash
cd to 3rdparty\ncnn\
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake.exe -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - NMake Makefiles" . -B bin64 && cmake.exe --build bin64
````
CLion is strongly recommended for the build. Please setup CLion as follows: 
![ncnnRay++ Code](https://github.com/QuantScientist/ncnnRay/blob/master/asstes/clion.png?raw=true)
   
Then cd to the root folder of thie project and run again:
````bash
cd to the root folder
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake.exe -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - NMake Makefiles" . -B bin64 && cmake.exe --build bin64
````
## Downloading and installing steps rayLib:
The **CMake file will download this automatically for you**.
 
## Contributing

Feel free to report issues during build or execution. We also welcome suggestions to improve the performance of this application.
 

## Citation

If you find the code or trained models useful, please consider citing:

```
@misc{ncnnRay++,
  author={Kashani, Shlomo},
  title={ncnnRay++2020},
  howpublished={\url{https://github.com/QuantScientist/ncnnRay/}},
  year={2020}
}
```
 
## Disclaimers
 
 - No liability. Feel free to submit bugs or fixes.
 - No tech support: this is merely a spare-time fun project for me.
 - Contribution is more than welcomed though.
 - Tested only on Windows 10 with Visual Studio 2019. More OS and dev env support are welcomed.

## Licensing

- Copyright © [Shlomo Kashani, author of the book "Deep Learning Interviews"](www.interviews.ai)

## Third party licences:
- raylib is licensed under an unmodified zlib/libpng license, which is an OSI-certified, 
BSD-like license that allows static linking with closed source software. Check LICENSE for further details.

- NVIDIA CUDA license https://docs.nvidia.com/cuda/eula/index.html 

# References

- https://github.com/RobLoach/raylib-cpp