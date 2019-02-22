# 241-Security-Project
## Exact Tasks / Goals
1. Learn about spectre, meltdown, and rootkits in depth	 
2. Create meltdown proof of concept
3. Create a rootkit possibly using our proof of concept or try a different angle, in our final presentation we’d like to show off a program that can find sensitive information on a system and send it to a different system
---
## Technical Specifications
1. Project will be written in C / bash
2. Will need to learn how kernel modules work to add more to this section

---
## Milestones
1. Week 3 and 4, 2/16 - 3/2
    1. Recreate meltdown from githubs, research in depth meltdown and spectre, research in depth rootkits and how we can use meltdown or spectre to build one
    2. Experiment finding sensitive information with our recreation of meltdown 
2. 3/13 - Midterm Presentation:
    1. Present a PoC of meltdown at the Midterm Presentation
3. Week 5 and 6, 3/2 - 3/16
    1. Look around and play with simple rootkits from github
    2. Recreate a simple rootkit
        1. Ex. a kernel module which intercepts every read system call
4. Week 7 and 8, 3/16 - 3/30
    1. Write a complete version of our rootkit - intercepting system calls, opening a network connection, and possibly trying to avoid basic firewall protections 
5. Week 9 and 10, 3/30 -  4/13
    1. Continue working on rootkit
    2. Combine our rootkit with our recreation of meltdown if our meltdown recreation worked
6. Week 11 and 12, 4/13 - 4/27
    1. Finish and cleanup whatever is left of project
    2. Documenting code, small bug fixes. getting ready for presentation
---
## Project Collaborators
Will Albers, Sayan Bhattacharjee, Ishan Shah (mentor), Ophir Sneh (mentor)
