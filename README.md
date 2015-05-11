Motion Estimatimation Simulation Program

## Description
This is a simulation program for motion estimation.

## Requirement
* Qt for MinGW (>=5.4)

## Compile
1. Open **me.pro**.
2. Run. (Ctrl+R)

## Example output
    grayscale	Fullsearch 8bit	Fullsearch 4bit 4pix
    blue_sky	566	646
    pedestrian_area	1106	1176
    riverbed	2544	2585
    rush_hour	702	778
    station2	612	661
    sunflower	505	566
    tractor	1021	1071

## Output
All line of output is formatted tab-separated values.
The first line of the output gives search method.
Each contains image name and average sum of absolute difference(SAD).

## Code reading
### Prefix
#### prev
*prev* means previous.  
`prev_image`,

#### curr
*curr* means current.  
`curr_image`

#### pel
*pel* means pixel.  
`pel_tb`, `pel_sw`

### Suffix
#### tb
*tb* means template block.  
`pel_tb`, `size_sw`

#### sw
*sw* means search window.  
`pel_sw`, `size_tb`

### Function Prototype
#### Processor Element
This function takes two pixel values and returns difference of those pixels.
    int
    pe_8bit(
      int pel_tb,
      int pel_sw
    );

#### Search method
This function takes two pointer to the image, size of template block, size of search range and function pointer to processor element and returns average SAD.
    int
    fullsearch(
      struct img_t *prev_image, //  pointer to previous frame
      struct img_t *curr_image, //  pointer to current frame
      int tb_size,              // size of template block
      int sw_range,             // size of search range
      int (*pe)(int , int)      // function pointer to processor element
    );
