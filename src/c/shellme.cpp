#include <phpcpp.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/seccomp.h>
#include <sys/ptrace.h>
#include <linux/audit.h>
#include <sys/prctl.h>

#define DEBUG 0

extern "C" {

   void shell_this(char* the_shell)
   {
	  int len = strlen(the_shell);
	  void *ptr = mmap(0, len, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	  void (*shell)();
	  
	  memcpy(ptr, the_shell, len);


	  // Set an alarm
	  if (!DEBUG)
	  {
		 alarm(30);
	  }

	  // seccomp	  
	  //seccomp(SECCOMP_SET_MODE_STRICT, 0, NULL);
	  prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

	  // exec	  
	  shell = (void (*)()) ptr;
	  shell();

	  return;
   }
   
}

Php::Value shellme (Php::Parameters &params)
{
   std::string shell = params[0];
   char* the_shell = (char*)shell.c_str();

   shell_this(the_shell);

   return true;
}


/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension myExtension("shellme", "1.0");

		myExtension.add<shellme>("shellme", {
			  Php::ByVal("shell", Php::Type::String),
		});

        // return the extension
        return myExtension;
    }
}

