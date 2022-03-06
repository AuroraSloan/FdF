# FdF

![pylone2.fdf](https://media.giphy.com/media/znvMs3nbjI6Bs3TqrS/giphy.gif)

 This program reads data points representing elevation from an `.fdf` file and connects the data points with lines, ultimately displaying a 3D wireframe representation. 
 
 There are two available options for formatting an fdf file. 
 
 The simplest version requires numbers to be written in the file with spaces in between each data point and a new line character for each row of data. 
 
 The other version includes the option to select a color for each data point. In this case, just write a comma and a the color in hexadecimal represenation right after the data point. 
 
 For example: `10,0x802020`

----
Both isometric and parallel views can be accessed any time by pressing ``i`` or ``p``
#### Isometric
![Imgur](https://i.imgur.com/5izB50O.png)

#### Parallel
![Imgur](https://i.imgur.com/UXsCMyy.png)

The image is also interactive and can be modified with the following controls.
|           | Smaller | Greater |
|-----------|---------|---------|
|Scale      |  ``f``  |  ``j``  |
|Depth      |  ``-``  |  ``+``  |

|Rotation   | Left  |  Right |
|-----------|-------|--------|
|x-axis     | ``a`` |  ``;`` |
|y-axis     | ``s`` |  ``l`` |
|z-axis     | ``d`` |  ``k`` |

|Translation |        |
|------------|--------|
|Left        |  ``←`` |
|Right       |  ``→`` |
|Up          |  ``↑`` | 
|Down        |  ``↓`` | 

----
### Installation
```bash
git clone https://github.com/AuroraSloan/FdF.git
```
----
## Usage
First, create the executable with make
```bash
make - compiles the FdF executable
make clean - removes all object files
make fclean - removes all object files and the executable
make re - removes all object files and the executable before recompiling the program
```
In order to run the program, run the executable with the .fdf file of your choice (fdf files are stored in the `maps` directory).
```bash
./fdf maps/50-4.fdf
```
To exit the program, you can press ``Esc`` or the red X in the top corner of the window
