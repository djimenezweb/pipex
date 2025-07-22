# Pipex tests

### 1. Comandos normales

Count how many lines are in `input.txt`, and write that number to `output.txt`.

>  NOTE: It counts the number of **newline characters**, not the number of visible lines or text blocks.
```
./pipex input.txt "cat" "wc -l" output_pipex.txt
< input.txt cat | wc -l > output_shell.txt
```

#### 1.1. Múltiples comandos normales
```
./pipex input.txt "cat" "grep line" "wc -l" output_pipex.txt
< input.txt cat | grep line | wc -l > output_shell.txt
```

### 2. Comandos más complejos
```
./pipex input.txt "ls -l -a" "grep .c" output_pipex.txt
< input.txt ls -l -a | grep .c > output_shell.txt
```

### 3. Input file inexistente
```
./pipex nofile.txt "cat" "wc" output_pipex.txt
{ < nofile.txt cat | wc; } > output_shell.txt
```

### 4. Directorio de outfile inexistente
```
./pipex input.txt "cat" "wc" missingdir/output_pipex.txt
{ < input.txt cat | wc > missingdir/output_shell.txt; }
```

### 5. No hay argumentos
```
./pipex > output_pipex.txt
{ > output_shell.txt; }
```

### 6. Comando está vacío
```
./pipex input.txt "" "wc -l" output_pipex.txt
( < input.txt "" | wc -l ) > output_shell.txt
```

### 7. Ambos comandos vacíos
```
./pipex input.txt "" "" output_pipex.txt
( < input.txt "" | "" ) > output_shell.txt
```

### 8. Comando no existente
```
./pipex input.txt noexistente "wc -l" output_pipex.txt
( < input.txt noexistente | wc -l  ) > output_shell.txt
```

### 9. Infile vacío
```
./pipex infile_empty "cat" "wc -l" output_pipex.txt
( < infile_empty cat | wc -l ) > output_shell.txt
```

### 10. Outfile sin permisos
```
./pipex input.txt "cat" "wc -l" out_no.txt
< input.txt (cat | wc -l > out_no.txt)
```

### 11. Comando con espacios
```
./pipex input.txt "grep 'hoy me siento'" "wc -l" output_pipex.txt
( < input.txt grep 'hoy me siento' | wc -l ) > output_shell.txt
```

### 12. Ruta del comando absoluta
```
./pipex input.txt "/bin/ls" "wc -l" output_pipex.txt
( < input.txt /bin/ls | wc -l ) > output_shell.txt
```

### 13. Infile es un directorio
```
./pipex infile_dir "cat" "wc -l" output_pipex.txt
( < infile_dir cat | wc -l ) > output_shell.txt
```

### 14. Comando termina en "/"
```
./pipex input.txt "/bin/" "wc -l" output_pipex.txt
( < input.txt /bin/ | wc -l ) > output_shell.txt
```

### 15. Outfile no creado
```
./pipex input.txt "cat" "wc -l" output_pipex.txt
( < input.txt cat | wc -l ) > output_shell.txt
```

### 16. Comandos vacíos + Outfile no existe
```
 ./pipex input.txt "" "" output_pipex.txt
( < input.txt "" | "" ) > output_shell.txt
```

### 17. Ambos archivos incorrectos
```
./pipex inpu.txt "/bin/" "wc -l" out/output_pipex.txt
 ({ < nofile.txt cat | wc; } > out/output_shell.txt)
 ```
 