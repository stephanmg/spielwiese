#include <iostream>
#include <vector>
#include <algorithm>

//The OpenCL C++ bindings, with exceptions
#define __CL_ENABLE_EXCEPTIONS
#include "CL/cl.hpp"

const size_t problemSize = 1024;

//The compute kernel we will run
const char * kernelSrc = 
  "__kernel void squareArray(__global float* input, "
  "                          __global float* output)"
  "{"
  "  output[get_global_id(0)] = input[get_global_id(0)] * input[get_global_id(0)];"
  "}";

int main()
{
  try {
    /***************     OpenCL Initialisation      ***************/
    //Open a context to run the openCL kernel in
    cl::Context context(CL_DEVICE_TYPE_GPU);

    //Gather all the kernel sources for the OpenCL program
    cl::Program::Sources source;
    source.push_back(std::make_pair(kernelSrc, strlen(kernelSrc)));
  
    //Make an OpenCL program
    cl::Program program(context, source);
  
    //Get all the available devices in the context
    std::vector<cl::Device> devices 
      = context.getInfo<CL_CONTEXT_DEVICES>();

    //Build the kernel sources for all devices in the context
    try {
      program.build(devices);
    }
    catch (cl::Error& err)
      {
	//Get the build log for the first device
	std::cerr << "Building failed, " << err.what() << "(" << err.err() << ")" 
		  << "\nRetrieving build log\n"	
		  << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0])
		  << "\n";
	return -1;
      }

    //Get the squareArray kernel to use in calculations
    cl::Kernel kernel(program, "squareArray");
  
    //Make a queue to put jobs on the first compute device
    cl::CommandQueue cmdQ(context, devices[0]);

    /***************   Preparing the data buffers   ***************/

    //Create a vector of random input values
    std::vector<cl_float> input;
    std::generate_n(std::back_inserter(input), problemSize, rand);

    //Start copying this data to the graphics card
    cl::Buffer inputBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * input.size(), &input[0]);
  
    //Make a buffer to hold the output of the kernel
    cl::Buffer outputBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_float) * input.size());
  

    /***************  Running on the graphics card  ***************/

    //Set the two arguments of the squareArray kernel
    kernel.setArg(0, inputBuffer);
    kernel.setArg(1, outputBuffer);

    //Get a Functor which will run the kernel on every input item in blocks of 64 threads
    cl::KernelFunctor func = kernel.bind(cmdQ, cl::NDRange(input.size()), cl::NDRange(64));

    //Run the kernel and wait for it to finish
    func().wait();


    /***************  Checking the outputted data   ***************/
  
    //Make a buffer to hold the outputted data
    std::vector<cl_float> output(input.size());

    //Request a blocking copy of the data from the graphics card
    cmdQ.enqueueReadBuffer(outputBuffer, true, 0, sizeof(cl_float) * input.size(), &output[0]);

    //Now check the answer
    for (size_t i(0); i < input.size(); ++i)
      if (input[i]*input[i] != output[i]) 
	std::cout << "Found a mistake " << input[i] << "^2 != " << output[i] << "\n";

    std::cout << "Finished!\n";
    return 0;
  }
  catch (cl::Error& err)
    {
      std::cerr << "An OpenCL error occured, " << err.what()
		<< "\nError num of " << err.err() << "\n";
      return -1;
    }
}
