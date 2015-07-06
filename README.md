Motion Estimatimation Simulation Program

## Description
This is a simulation program for motion estimation.

## Requirement
* Qt for MinGW (>=5.4)

## Compile
1. Open **motion_estimation.pro**.
2. Run. (Ctrl+R)

## Code reading
### Structures
*mvec_t*--
motion vector

*mvec_table_t*--
table of motion vector

*me_block_t*--
motion estimation block

### Prefixies
#### prev
*prev* means previous.  
`prev_frame`

#### curr
*curr* means current.  
`curr_frame`

### Function Prototypes
This function takes a pointer to *struct me_block_t*. This function computes motion vectors.
    int
    fullsearch(
      struct me_block_t *me_block // pointer to motion estimation block
    );
