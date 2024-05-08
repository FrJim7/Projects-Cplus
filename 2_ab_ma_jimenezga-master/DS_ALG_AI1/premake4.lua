-- ---------------------------------
-- Toni Barella
-- Algoritmos & Inteligencia Artificial
-- ESAT 2016-2019
-- Genie Project Configuration.
-- ---------------------------------

solution ("DS_ALG_AI1" .. _ACTION)
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	language "C"
	kind "ConsoleApp"
	location ("build")	
	
	projects = { "PR0_MemoryNode", "PR1_Vector", "PR2_List", "PR3_DLList", "PR4_Stack", "PR5_Queue", "PR6_Comparative" }

	for i, prj in ipairs(projects) do 
		project (prj)
		targetname (prj)
		language "C"
		prj_path = "./build/" .. prj

		location (prj_path .. "/" .. _ACTION)
		
		includedirs {
			"./include/",
			"./deps/include/",
		}
		libdirs { "./deps/lib/ABGS_MemoryManager" }

		files {
			"./include/*.h",
			"./deps/include/*.h",
			"./deps/include/ABGS_MemoryManager/*.h",
		}
	
	    defines { "_CRT_SECURE_NO_WARNINGS" }
        flags { "ExtraWarnings" }

		configuration "vs2015"
		  windowstargetplatformversion "8.1"

		configuration "vs2017"
		    --windowstargetplatformversion "10.0.15063.0"
			--windowstargetplatformversion "10.0.16299.0"
			windowstargetplatformversion "10.0.17134.0"
			--windowstargetplatformversion "10.0.17134.471"

		configuration "Debug"
			defines { "DEBUG" }
			targetdir ("bin/Debug")
			targetsuffix "_d"
			objdir ("build/" .. "Debug")
			flags { "Symbols", "NoPCH" }
			links { "ABGS_MemoryManager_w32d" }
			--links { "ABGS_MemoryManager_w64d" }

		configuration "Release"
			targetdir ("bin/Release")
			objdir ("build/" .. "Release")
			flags { "Optimize", "NoPCH" }
			links { "ABGS_MemoryManager_w32" }
			--links { "ABGS_MemoryManager_w64" }

	end

	    project "PR0_MemoryNode"
			files {
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./tests/test_memory_node.c",
		}

		project "PR1_Vector"
			files {
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./include/adt_vector.h",
			"./src/adt_vector.c",
			"./tests/test_vector.c",
		}

		project "PR2_List"
			files {
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./include/adt_list.h",
			"./src/adt_list.c",
			"./tests/test_list.c",
		}

		project "PR3_DLList"
			files {
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./include/adt_dllist.h",
			"./src/adt_dllist.c",
			"./tests/test_dllist.c",
		}

		project "PR4_Stack"
			files {
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./include/adt_vector.h",
			"./src/adt_vector.c",
			"./src/adt_stack.c",
			"./include/adt_stack.h",
			"./tests/test_stack.c",
		}

		project "PR5_Queue"
			files {
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./include/adt_list.h",
			"./src/adt_list.c",
			"./src/adt_queue.c",
			"./include/adt_queue.h",
			"./tests/test_queue.c",
		}

		project "PR6_Comparative"
			files {
			"./comparative/comparative.c",
			"./include/adt_memory_node.h",
			"./src/adt_memory_node.c",
			"./include/adt_vector.h",
			"./src/adt_vector.c",
			"./include/adt_dllist.h",
			"./src/adt_dllist.c",
			"./include/adt_list.h",
			"./src/adt_list.c",
		}