# termux-cmd v1.0.0

**cmd.exe (Microsoft Windows Server 2003) rodando 100% nativo no Termux — ARM64/bionic, sem root, sem emulação.**

## O que é

Port do `cmd.exe` oficial do Windows Server 2003 compilado como ELF ARM64 nativo para Android/bionic, direto no Termux. Nada de wine, box64, qemu, proot ou chroot — syscalls nativas, feito em C puro com um shim de Win32 APIs (`portable/`).

## Destaques

- **100% nativo** — ELF aarch64 bionic, sem emulação de nenhum tipo
- **Comandos funcionais**: `dir`, `cd`, `type`, `copy`, `del`, `ren`, `md`, `rd`, `echo`, `ver`, `date`, `time`, `vol`, `path`, `set`
- **Legado real** — código-fonte original da Microsoft (Server 2003 / NT4 / WinCE auditados)
- **Sobrevive a segfaults** — handler de sinal com `siglongjmp` devolve ao prompt em vez de crashar
- **Compatibilidade de path** — aceita tanto `\` quanto `/` como separador
- **Delimitado por testes** — suíte automatizada (`scripts/run_tests.sh`)

## Instalação

```bash
# Do release (em breve): baixar o binário `cmd.exe`
# Ou build direto:
git clone https://github.com/rianprei/termux-cmd.git
cd termux-cmd
make
./cmd.exe
```

## Documentação

- [README](https://github.com/rianprei/termux-cmd/blob/main/README.md)
- [Arquitetura](https://github.com/rianprei/termux-cmd/blob/main/docs/architecture.md)
- [Comandos suportados](https://github.com/rianprei/termux-cmd/blob/main/docs/commands.md)
- [Batch](https://github.com/rianprei/termux-cmd/blob/main/docs/batch.md)
- [Porting/Win32 shims](https://github.com/rianprei/termux-cmd/blob/main/docs/porting.md)
- [Troubleshooting](https://github.com/rianprei/termux-cmd/blob/main/docs/troubleshooting.md)
- [Changelog](https://github.com/rianprei/termux-cmd/blob/main/CHANGELOG.md)

## Licença

MIT (código original da Microsoft redistribuído conforme os termos do Windows Server 2003 — ver LICENSE).