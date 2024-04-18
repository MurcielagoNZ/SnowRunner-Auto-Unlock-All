# 《雪地奔驰》全解锁工具 SnowRunner Auto Unlock All Tool

这是一个半自动的小工具，帮助修改《雪地奔驰》的游戏文件。这个小工具可以帮你解锁物品的地区、级别限制，并让需要探索才能解锁的物品直接可用。<br>
This is a semi-automatic tool designed to assist in modifying game files for 《SnowRunner》. The tool can unlock region and level restrictions for items and make items that require exploration directly accessible.<br>

将initial.pak中的[media]文件夹拷贝到项目文件夹中，并且运行（F5）代码，或者将编译好的程序和解压出来的[media]文件夹放在同一目录下运行。这将修改[media]文件夹下的对应文件，并删除不需要修改的文件。完成后，将[media]文件夹更新到initial.pak中即可。<br>
Copy the [media] folder in the initial.pak to the project folder, and run (F5) the code. Or just use the exe, put the exe and unziped [media] folder into same directory. It will modify the corresponding files under the [media] folder and delete the files that do not need to be modified. After completion, update the [media] folder to initial.pak.<br>

因为我太懒了，我用递归和系统栈扫描文件夹，所以记得在项目属性里调一下系统栈……<br>
Because I'm too lazy, I used recursion and system stack to scan folders, so remember to adjust the system stack in the project properties...<br>
<br>
Have fun!<br>
<br>
<br>
新增：<br>
* 可以将不支持全驱的车辆改为全驱（可选）
* 可以将不支持差速锁的车辆的差速器焊死（差速锁常锁）（可选）（推荐）

New:<br>
* Vehicles that do not support all-wheel drive can be changed to all-wheel drive (optional)
* The differential of vehicles that do not support differential lock can be welded (i.e. the differential lock is always locked) (optional) (recommended)
