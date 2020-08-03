# -dir-er-for-vk-styles
Easy programm with a narrow application. Adds `[dir]` in every block which name contains "."
in other words, conferts something like this:
```
.ui_search_sugg_list .ui_search_sugg_history_header
{color:lime}
.wcommunity_name .wcommunity_name_link, .post_author .author, .wall_module .author, .page_group_name, .wall_module .copy_author
{color:orange}
.post_author:hover .author, .wall_module .author:hover
{color: #ffca00}
.wcommunity_post_date
{color:yellow}
```
into this
```
[dir] .ui_search_sugg_list .ui_search_sugg_history_header
{color:lime}
[dir] .wcommunity_name .wcommunity_name_link, [dir] .post_author .author, [dir] .wall_module .author, [dir] .page_group_name, [dir] .wall_module .copy_author
{color:orange}
[dir] .post_author:hover .author, [dir] .wall_module .author:hover
{color: #ffca00}
[dir] .wcommunity_post_date
{color:yellow}
```
Why? If you asking this, you don't need that program.
## How to use English
1. "Выбрать путь по умолчанию?"
* That's path to your text file with your css code that you want to `[dir]`
* if you type `yes` or `y` or `1`, the path for file will be "C:\css.txt"
* if negative, you will type the path
2. "Выбрать текст по умолчанию?"
* text that is added before every block which name contains "."
* if positive, text is `[dir]`
* if negative, you type the text
3. If completed, it'll write `[dir]ирование кода завершено!`, `[dir]ed` code will be in the same folder and have a name with  `_fixed` postfix
