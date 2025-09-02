# Llama2 Tokenizer for Vitis ARM Platform

This application implements a Llama2 tokenizer using Google's SentencePiece library, built for ARM processors using Xilinx Vitis tools. The application can encode text to token IDs and decode token IDs back to text, while also providing access to token embeddings.

## Features

- **Text Encoding**: Convert text input to token IDs using SentencePiece
- **Text Decoding**: Convert token IDs back to readable text
- **Embedding Access**: Load and display token embeddings from binary files
- **Interactive CLI**: Choose between encoding and decoding modes at runtime

## Architecture

- **Target Platform**: ARM64 (Cortex-A72)
- **Operating System**: Linux (PetaLinux)
- **Build System**: CMake with Xilinx Vitis tools
- **Main Dependencies**: SentencePiece library

## Prerequisites

### Hardware Requirements
- Xilinx development board with ARM Cortex-A72 processor
- Compatible Vitis platform

### Software Requirements
- Xilinx Vitis 2025.1 or compatible version
- PetaLinux SDK with ARM sysroot
- **SentencePiece library built for ARM architecture**

## Important: SentencePiece ARM Build Requirement

⚠️ **Critical Note**: The SentencePiece library must be compiled specifically for ARM processors to work with this application. The standard x86 builds will not be compatible.

### Building SentencePiece for ARM

1. **Cross-compilation Setup**: Ensure you have the ARM cross-compilation toolchain from your PetaLinux installation
2. **SentencePiece Source**: Download the SentencePiece source code from [Google's repository](https://github.com/google/sentencepiece)
3. **ARM Configuration**: Configure the build to target ARM64 architecture using the same sysroot as specified in the project:
   ```bash
   # Example configuration for ARM cross-compilation
   cmake -DCMAKE_TOOLCHAIN_FILE=<path_to_arm_toolchain> \
         -DCMAKE_SYSROOT=/opt/petalinux/2025.1/sysroots/cortexa72-cortexa53-amd-linux \
         -DCMAKE_SYSTEM_PROCESSOR=aarch64 \
         <sentencepiece_source_dir>
   ```
4. **Installation**: Install the compiled library to a location accessible during the build process

## Project Structure

```
app_component/
├── CMakeLists.txt          # Main CMake configuration
├── UserConfig.cmake        # User-customizable build settings
├── vitis-comp.json         # Vitis component configuration
├── src/
│   ├── tokenizer.cpp       # Main application logic
│   ├── tokenizer.h         # Embedding loader class
│   ├── tokenizer.model     # SentencePiece model file
│   ├── embeddings.bin      # Binary embedding data
│   └── embeddings_info.txt # Embedding metadata
├── build/                  # Build output directory
└── _ide/                   # IDE configuration files
```

## Required Files

Before building, ensure you have the following model files in the `src/` directory:

1. **`tokenizer.model`**: SentencePiece model file for Llama2
2. **`embeddings.bin`**: Binary file containing token embeddings
3. **`embeddings_info.txt`**: Text file with embedding metadata (vocab size and dimension)

### Example Usage

**Encoding Text:**
```
Choose mode:
1. Encode text to token IDs
2. Decode token IDs to text
Enter your choice (1 or 2): 1
Enter text to encode: Hello world
Encoded IDs: 15043 3186 
Embedding for each token:
Token ID 15043: -0.123 0.456 -0.789 0.321 -0.654
Token ID 3186: 0.987 -0.234 0.567 -0.890 0.123
```

**Decoding Token IDs:**
```
Choose mode:
1. Encode text to token IDs
2. Decode token IDs to text
Enter your choice (1 or 2): 2
Enter token IDs separated by spaces: 15043 3186
Hello world
```

## Configuration

### CMake Variables

Key configuration options can be modified in `UserConfig.cmake`:

- **USER_COMPILE_DEFINITIONS**: Additional compiler definitions
- **USER_COMPILE_OPTIONS**: Custom compiler flags
- **USER_INCLUDE_DIRECTORIES**: Additional include paths
- **USER_LINK_LIBRARIES**: Additional libraries to link
- **USER_LINK_DIRECTORIES**: Additional library search paths

### Platform Configuration

The target platform is configured in `vitis-comp.json`:
- **CPU Instance**: cortex-a72
- **Domain**: linux_psv_cortexa72
- **Sysroot**: PetaLinux ARM sysroot path

## Troubleshooting

### Common Issues

1. **SentencePiece Library Not Found**
   - Ensure SentencePiece is built for ARM architecture
   - Verify library paths in CMake configuration
   - Check sysroot contains the ARM-compiled library

2. **Model File Not Found**
   - Ensure `tokenizer.model` is in the same directory as the executable
   - Verify file permissions and accessibility

3. **Embedding Loading Errors**
   - Check that `embeddings_info.txt` format is correct
   - Verify `embeddings.bin` file size matches expected dimensions
   - Ensure both files are accessible to the application

### Build Errors

- **Cross-compilation Issues**: Verify ARM toolchain setup and sysroot configuration
- **Missing Dependencies**: Ensure all required libraries are available in the ARM sysroot
- **Vitis Environment**: Confirm Vitis tools are properly sourced and configured

## Contributing

When contributing to this project, please ensure:
- All changes maintain ARM compatibility
- SentencePiece library requirements are updated accordingly
- Build instructions remain accurate for the target platform
