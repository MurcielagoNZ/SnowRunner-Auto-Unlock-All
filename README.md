# 《雪地奔驰》全解锁工具 SnowRunner Auto Unlock All Tool

这是一个半自动的小工具，帮助修改《雪地奔驰》的游戏文件。这个小工具可以帮你解锁物品的地区、级别限制，并让需要探索才能解锁的物品直接可用。
This is a semi-automatic tool designed to assist in modifying game files for 《SnowRunner》. The tool can unlock region and level restrictions for items and make items that require exploration directly accessible.

新建一个Visual Studio项目，导入代码，将initial.pak中的[media]文件夹拷贝到项目文件夹中，并且运行（F5）代码。这将修改[media]文件夹下的对应文件，并删除不需要修改的文件。完成后，将[media]文件夹更新到initial.pak中即可。
Create a new Visual Studio project, import the code, copy the [media] folder in the initial.pak to the project folder, and run (F5) the code. This will modify the corresponding files under the [media] folder and delete the files that do not need to be modified. After completion, update the [media] folder to initial.pak.

因为我太懒了，我用递归和系统栈扫描文件夹，所以记得在项目属性里调一下系统栈……
Because I'm too lazy, I used recursion and system stack to scan folders, so remember to adjust the system stack in the project properties...

Have fun!
