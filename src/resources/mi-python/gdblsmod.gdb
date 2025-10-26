#gdb implementation of the linux lsmod
define gdblsmod
    set $current = modules.next
    set $offset =  ((int)&((struct module *)0).list)
    printf "Module\tAddress\n"

    while($current != &modules)
        set $mod = ((struct module *) (((void *) ($current)) - $offset ))
        printf "%s\t\n", $mod->name
        set $current = $current->next
    end
end
