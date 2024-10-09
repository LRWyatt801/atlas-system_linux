#!/usr/bin/python3
"""Proc file manipulation"""
    
import sys

def get_args():
    """parses input arguments
    'USAGE: read_write_heap.py <pid> <search_str> <replace_str>'
    """
    if len(sys.argv) < 3:
        print(f"USAGE: : read_write_heap.py <pid> <search_str> <replace_str:optional>")
        exit(1)
    
    pid = sys.argv[1]
    search_str = sys.argv[2]
    
    if len(sys.argv) == 4:
        replace_str = sys.argv[3]
    else:
        replace_str = None # set replace_str to none for future check

    return pid, search_str, replace_str

def get_mem_address(pid):
    """Retrieves the memory address range for the heap of a running process

    Args:
        pid (int): Process ID

    Returns:
        int: starting and ending memory address of heap
    """

    if pid == None:
        exit(1)
    map_file = f"/proc/{pid}/maps"
    
    try:
        with open(map_file) as map:
            for line in map:
                if "[heap]" in line:
                    adrs_rng = line.split()[0]
                    strt_adrs, end_adrs = adrs_rng.split("-")
                    
                    strt_adrs = int(strt_adrs, 16)
                    end_adrs = int(end_adrs,16)
                    
                    return strt_adrs, end_adrs
    
    except FileNotFoundError:
        print(f"/proc/{pid}/maps: not found")
        exit(1)

def replace_heap_str(
                     pid,
                     strt_adrs,
                     end_adrs,
                     search_str,
                     replace_str = None):
    """Searchs process heap to replace search_str with replace_str

    Args:
        pid (int): Process ID
        strt_adrs (int): Starting memory address of heap
        end_adrs (int): Ending memory address of heap
        search_str (str): String to replace
        replace_str (str, optional): String to be used to replace. Defaults to None or ""(empty str).
    """
    if pid == None or strt_adrs == None or end_adrs == None or \
    search_str == None:
        exit(1)
    
    if replace_str == None:
        replace_str = ""
        
    if len(replace_str) > len(search_str):
        print(f"Error: {replace_str} is longer than {search_str}")
        exit(1)
    elif len(replace_str) < len(search_str):
        len_diff = len(search_str) - len(replace_str)
        replace_str += " " * len_diff

    mem_file = f"/proc/{pid}/mem"
    
    try:
        with open(mem_file, "+br") as mem:
            
            mem.seek(strt_adrs)
            
            heap_size = end_adrs - strt_adrs
            heap_read = mem.read(heap_size)
            
            search_bytes = search_str.encode('ascii')
            write_bytes = replace_str.encode('ascii')
            found = heap_read.find(search_bytes)
            if found == -1:
                print(f"{search_str} not found in heap")
                exit(1)
            
            mem.seek(strt_adrs + found)
            mem.write(write_bytes)
        
    except PermissionError:
        print(f"{mem_file}: Permission Denied, try running as root user")
        exit(1)
    
    except FileNotFoundError:
        print(f"Process: {pid} not found")
        exit(1)
    
    except Exception as e:
        print(f"Error: {e}")
        exit(1)

if __name__ == "__main__":
    """Entry point for python program"""
    pid, search_str, replace_str = get_args()
    strt_adrs, end_adrs = get_mem_address(pid)
    replace_heap_str(
                     pid,
                     strt_adrs,
                     end_adrs,
                     search_str,
                     replace_str)
    
    
