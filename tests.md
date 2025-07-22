# Pipex tests

#### 1. Comandos normales

Count how many lines are in input.txt, and write that number to out1_shell.txt.

>  NOTE: It counts the number of **newline characters**, not the number of visible lines or text blocks.
```
./pipex input.txt "cat" "wc -l" out1.txt 2> errores1.txt

< input.txt cat | wc -l > out1_shell.txt 2> errores1_shell.txt
```

#### 2. Comandos más complejos
```
./pipex input.txt "ls -l -a" "grep .c" out1.txt 2> errores1.txt

< input.txt ls -l -a | grep .c > out1_shell.txt 2> errores1_shell.txt
```

#### 3. Input file inexistente
```
./pipex nofile.txt "cat" "wc" out1.txt 2> errores1.txt

{ < nofile.txt cat | wc; } > out1_shell.txt 2> errores1_shell.txt
```

#### 4. Directorio de outfile inexistente
```
./pipex input.txt "cat" "wc" missingdir/out1.txt 2> errores1.txt

{ < input.txt cat | wc > missingdir/out1.txt; } 2> errores1_shell.txt
```

#### 5. No hay argumentos
```
./pipex > out1.txt 2> errores1.txt

{ > out1_shell.txt; } 2> errores1_shell.txt
```

#### 6. Comando está vacío
```
./pipex input.txt "" "wc -l" out1.txt 2> errores1.txt

( < input.txt "" | wc -l ) > out1_shell.txt 2> errores1_shell.txt
```

#### 7. Ambos comandos vacíos
```
./pipex input.txt "" "" out1.txt 2> errores1.txt

( < input.txt "" | "" ) > out1_shell.txt 2> errores1_shell.txt
```

#### 8. Comando no existente
```
./pipex input.txt noexistente "wc -l" out1.txt 2> errores1.txt

( < input.txt noexistente | wc -l  ) > out1_shell.txt 2> errores1_shell.txt
```

#### 9. Infile vacío
```
./pipex infile_empty "cat" "wc -l" out1.txt 2> errores1.txt

( < infile_empty cat | wc -l ) > out1_shell.txt 2> errores1_shell.txt
```

#### 10. Outfile sin permisos
```
./pipex input.txt "cat" "wc -l" out_no.txt 2> errores1.txt

< input.txt (cat | wc -l > out_no.txt) 2> errores1_shell.txt
```

#### 11. Comando con espacios
```
./pipex input.txt "grep 'hoy me siento'" "wc -l" out1.txt 2> errores1.txt

( < input.txt grep 'hoy me siento' | wc -l ) > out1_shell.txt 2> errores1_shell.txt
```

#### 12. Ruta del comando absoluta
```
./pipex input.txt "/bin/ls" "wc -l" out1.txt 2> errores1.txt

( < input.txt /bin/ls | wc -l ) > out1_shell.txt 2> errores1_shell.txt
```

#### 13. Infile es un directorio
```
./pipex infile_dir "cat" "wc -l" out1.txt 2> errores1.txt

( < infile_dir cat | wc -l ) > out1_shell.txt 2> errores1_shell.txt
```

#### 14. Comando termina en "/"
```
./pipex input.txt "/bin/" "wc -l" out1.txt 2> errores1.txt

( < input.txt /bin/ | wc -l ) > out1_shell.txt 2> errores1_shell.txt
```

#### 15. Outfile no creado
```
./pipex input.txt "cat" "wc -l" out2.txt 2> errores1.txt

( < input.txt cat | wc -l ) > out2_shell.txt 2> errores1_shell.txt 
```

#### 16. Comandos vacío + Outfile no existe
```
 ./pipex input.txt "" "" out3.txt 2> errores1.txt

( < input.txt "" | "" ) > out3_shell.txt 2> errores1_shell.txt
```

#### 17. Ambos archivos incorrectos
```
./pipex inpu.txt "/bin/" "wc -l" out/out1.txt 2> errores1.txt

 ({ < nofile.txt cat | wc; } > out/out1_shell.txt) 2> errores1_shell
 ```
 