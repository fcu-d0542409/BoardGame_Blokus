# BoardGame_Blokus
## Introduction
- Blokus is the fast-paced strategy game that provides players a great experience with brainstorming, which has been invented in Germany in 2000.
- Related Documents: https://service.mattel.com/instruction_sheets/BJV44-Eng.pdf
- In following, I will show you how __design thinking__ of my algorithm in Blokus. 🧠🧠🧠
  ![image](https://user-images.githubusercontent.com/32485341/125181265-c61f0d80-e235-11eb-97c9-f5197b29b3de.png)
  ![image](https://user-images.githubusercontent.com/32485341/125181387-c7046f00-e236-11eb-9da6-71198f18e3cd.png)


## Basic Roles
1. The blocks in the same color can only touch angle by angle instead of side by side. 
    - The following are some type of correct putting operations. 
      - ![image](https://user-images.githubusercontent.com/32485341/125181516-1d25e200-e238-11eb-9bda-c111956ef7c0.png) ![image](https://user-images.githubusercontent.com/32485341/125181474-9bce4f80-e237-11eb-91e4-b133f4733f27.png) ![image](https://user-images.githubusercontent.com/32485341/125181499-f1a2f780-e237-11eb-8860-f6ffdc2a7272.png)
    - By contrast, below is an example with illegal putting operation.
      - ![image](https://user-images.githubusercontent.com/32485341/125181594-c66cd800-e238-11eb-8c12-95d5932a3552.png)

2.  The position where blocks is put needs to touch at least one of the same color blocks.
    - There is an coomon place of blocks on the checkboard. The __blue__ positions are some __attaching points__ which could be attach by the next putting blocks.
      - ![image](https://user-images.githubusercontent.com/32485341/125181741-90c8ee80-e23a-11eb-9799-436cfd5f9572.png)


## Demo 
https://user-images.githubusercontent.com/32485341/125150562-43ce1500-e173-11eb-9a99-020676d8f436.mp4

``` python
print('hello')
```
- a
- b
- c
🐥 // :+?
