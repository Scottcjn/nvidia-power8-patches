# Contributing to NVIDIA POWER8 Patches

Thank you for your interest in contributing to NVIDIA POWER8 Patches! This document provides guidelines and instructions for contributing.

## Code of Conduct

This project follows the [Contributor Covenant](CODE_OF_CONDUCT.md). By participating, you agree to uphold this code.

## How to Contribute

### Reporting Issues

- Check existing issues before creating a new one
- Use clear, descriptive titles
- Include system details (POWER8 model, NVIDIA GPU, driver version)
- Provide steps to reproduce any bugs

### Submitting Patches

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Make your changes
4. Test on POWER8 hardware if possible
5. Commit your changes (`git commit -m 'Add some feature'`)
6. Push to the branch (`git push origin feature/your-feature`)
7. Open a Pull Request

### Code Style

- Follow Linux kernel coding style for C code
- Use 8-space tabs for indentation
- Keep lines under 100 characters
- Add comments for POWER8-specific code

### Testing

Before submitting a PR:

1. Verify syntax: `gcc -fsyntax-only your-file.c`
2. Test build on POWER8 if available
3. Run `nvidia-smi` to verify driver loads correctly

## Development Setup

### Prerequisites

- IBM POWER8/9/10 system
- NVIDIA GPU (supported models)
- CUDA toolkit
- GCC compiler
- Linux kernel headers

### Building

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/nvidia-power8-patches.git
cd nvidia-power8-patches

# Apply patches to NVIDIA driver source
./apply-patches.sh /path/to/nvidia-driver-source

# Build
cd /path/to/nvidia-driver-source
make
sudo make install
```

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

🤝 Generated for the POWER8 community
