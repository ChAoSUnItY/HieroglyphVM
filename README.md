<h1> Hieroglyph Virtual Machine (HVM) </br>象形虛擬機 </h1>

##

> A Virtual Machine based on "Crafting Interpreter" but without GC, mainly designed for [Fang Yen Programming Language](https://github.com/ChAoSUnItY/FangYen) evaluation.  <br/>
> 一個依"Crafting Interpreter"一書所打造的虛擬機，不含GC，主要設計給[方言程式語言](https://github.com/ChAoSUnItY/FangYen) 運行.

## TODO

- addition, subtraction, etc.

## Spec

| OP          | Stack           | Info            |
|-------------|-----------------|-----------------|
| OP_CONSTANT | {} -> {s1}      | Loads constant value onto stack |
| OP_RETURN   | {} -> {} (HALT) | Returns last stack value or nil |

