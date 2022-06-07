OUTPUT_FORMAT(elf32-i386)
ENTRY(__load_entry)
 
SECTIONS
{
	. = 1M;

	
	.text : ALIGN(4K)
	{
		*(.multiboot)	
		*(.text)
	}
 
	
 
	.data : ALIGN(4K)
	{
		*(.rodata)

		create_instance = .;
		KEEP(*( .init_array ));
		KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
		destroy_instance = .;

		*(.data)
	}
 
	.bss : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

	.end : {
		_kstart_ = .;
		*(.end)
		. = ALIGN(4096);
	}
 
}
