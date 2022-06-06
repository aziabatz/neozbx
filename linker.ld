OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)
ENTRY(__load_entry)
 
SECTIONS
{
	. = 1M;

	.multiboot :
	{
		*(.multiboot)
	}
	
	.text :
	{
		
		*(.text)
	}
 
	
 
	.data :
	{
		*(.rodata)

		create_instance = .;
		KEEP(*( .init_array ));
		KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
		destroy_instance = .;

		*(.data)
	}
 
	.bss :
	{
		*(COMMON)
		*(.bss)
	}

	.end : {
		end = .;
		*(.end)
		. = ALIGN(4096);
	}
 
}
