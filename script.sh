#!/bin/bash
function create_file () {
    echo "Введите имя файла, которого хотите создать"
    read file_name

    if [ -f "$file_name" ]; then
        echo "Файл с таким именем уже существует"
        return 1
    fi
    
    touch $file_name
    return 0
}

function remove_file () {
    echo "Введите имя файла, которого хотите удалить"
    read file_name

    if [ ! -f "$file_name" ]; then
        echo "Такого файла не существует"
        return 1
    fi

    rm $file_name
    return 0
}

function move_file () {
    echo "Введите имя файла, которого хотите переместить"
    read file_name

    if [ ! -f "$file_name" ]; then
        echo "Такого файла не существует"
        return 1
    fi

    echo "Введите директорию"
    read dir_path
    if [ ! -d "$dir_path" ]; then
        echo "Такой директории не существует"
        return 1
    fi

    mv $file_name $dir_path
    return 0
}

echo "Программа работы с файлами и каталогами"
echo "С помощью данной программы вы можете перемещать, создавать и удалять файлы"
echo "Разработчик: Песняк Михаил"

while [ true ]; do 
    echo "Выберете операцию над файлом: 1 - создать, 2 - удалить, 3 - переместить, 4 - выйти из программы"
    read operation
    set return_code = 0
    case $operation in
         1) create_file; return_code=$? ;;
         2) remove_file; return_code=$? ;;
         3) move_file; return_code=$? ;;
         4) exit $return_code ;;
        *) echo "Not supported" ;;
esac   
done