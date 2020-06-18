# sffs

Stratify flash files system is a power-resilient wear-aware flash
file system for NAND flash memory or SD cards. It works with both
SPI flash devices or parallel flash chips.

# Design

This design description describes the filesystem from the bottom up.
We start with the physical flash memory, divide it in to blocks, then
use those blocks to store file data and list data for keeping track
of file and directory content.

## Blocks

`sffs` assumes the flash memory can be divided into eraseable blocks
and writable blocks. Most flash has pages which descibe the smallest
eraseable section. The writable block size is defined by SFFS and
is larger for better performance.

Each block of data can hold one of three types of information.

- File Data
- File List Data
- Directory Data (Full featured build only)
- Directory List Data (Full featured build only)
- Serial Number List Data

### The Scratch Pad

There is a special section of drive memory that is reserved for
the scratch pad. Once every block in the drive has been used, blocks
are freed by copying blocks that are still in use to the scratch pad,
deleting the flash page, then restoring the data from the scratch pad.

This operation is only required for memory that requires wear leveling.


## File Data

The file data stores the data for the file which and is associated
with the file using the file list data.

## File List Data

The file list data includes first a header including
the name of the file and a list of blocks that the file
is using for data storage. Each entry contains a block number
and a segment number. The block number represents the physical location
on the memory and the segment number represents the location
of the data in the file.

## Directory Data

The directory data contains the name and other metadata for the directory
as well as a list of serial numbers that are present in the directory.

## Directory List Data

...

## Serial Number List Data

Everytime a new file is created it is assigned a serial number.
There is a single root directly that keeps a list of serial number
entries. The entries include

- Entry state
- Serial number
- First list data

Each time a file is modified, the state of the serial number
is updated. Each time the entry is updated, the entry is marked as dirty
and a new entry is appended to the end of the list. This happens
in such a way that a power failure at any time cannot corrupt the
filesystem.

## Ways to improve performance

### Cache file list location and block

Each time the file is read, it looks up the file segment starting
at the beginning of the file list. This can take a long time to look
up for large files.  The same is true for writing large files.

The function to modify is sffs_file_loadsegment(). Add a sffs_list_t data
variable to the file handle. When looking for the next segment,
always start with the next entry in the list rather than starting over. That
can be done using sffs_list_getnext() and passing the current state of the
list. Re-init the list if the segment isn't found.

### Cleanup filesystem in the background

The scratch pad needs to run periodically (preferably in the background)
rather than running during an operation.

Create statistical triggers for cleaning the filesystem. As in
once, 90% of blocks are dirty, trigger a cleanup.

### Add a compile time switch to disable wear leveling

If wear leveling isn't needed, blocks can be erased as
soon as they become dirty. There is no need
to run a cleanup routine.

### Making blocks the same size as eraseable pages

The scratch pad is needed because eraseable pages are usually
larger than blocks. If they are the same size, there is no need
for the scratch.

### Large drives need a lookup table for the block allocator

A table (or list) needs to be implemented for large drives
to keep track of which blocks are in use. Maybe just take one bit
per block and block off a section of the drive so that
blocks can be allocated very fast.
