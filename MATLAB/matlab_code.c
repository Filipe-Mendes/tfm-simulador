#include <stdint.h>

__declspec(dllexport) void wrapper_c_coder_step(RT_MODEL_c_coder_T *const c_coder_M, 
	real_T c_coder_U_Inport, 
	real_T c_coder_U_Inport1, 
	real_T c_coder_U_Inport2,
	real_T c_coder_U_Inport3,
	real_T c_coder_U_Inport4, 
	real_T c_coder_U_Inport5) {
		

	c_coder_step(c_coder_M, c_coder_U_Inport, c_coder_U_Inport1, c_coder_U_Inport2,
               c_coder_U_Inport3, c_coder_U_Inport4, c_coder_U_Inport5);
        
	
}


__declspec(dllexport) void wrapper_c_coder_initialize(RT_MODEL_c_coder_T *const c_coder_M, 
	real_T c_coder_U_Inport, 
	real_T c_coder_U_Inport1, 
	real_T c_coder_U_Inport2, 
	real_T c_coder_U_Inport3, 
	real_T c_coder_U_Inport4, 
	real_T c_coder_U_Inport5) {
		
	c_coder_initialize(c_coder_M, &c_coder_U_Inport, &c_coder_U_Inport1,
                    &c_coder_U_Inport2, &c_coder_U_Inport3, &c_coder_U_Inport4,
					&c_coder_U_Inport5);
}

__declspec(dllexport) uint8_T *getOutput(){
   return out1;
}
