# HVMC (Hieroglyph VM class file) Spec

## File Format

<table class="tg">
<thead>
  <tr>
    <th class="tg-0pky">Byte Offset</th>
    <th class="tg-0pky">Size</th>
    <th class="tg-0pky">Type or Value</th>
    <th class="tg-0pky">Description</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-0pky">0</td>
    <td class="tg-0pky">4 bytes</td>
    <td class="tg-0pky">u1 = 0x43</td>
    <td class="tg-0pky">Magic number, represents `CASC`, used to identify this file as a HVMC file.</td>
  </tr>
  <tr>
    <td class="tg-0pky">1</td>
    <td class="tg-0pky"></td>
    <td class="tg-0pky">u1 = 0x41</td>
    <td class="tg-0pky"></td>
  </tr>
  <tr>
    <td class="tg-0pky">2</td>
    <td class="tg-0pky"></td>
    <td class="tg-0pky">u1 = 0x53</td>
    <td class="tg-0pky"></td>
  </tr>
  <tr>
    <td class="tg-0pky">3</td>
    <td class="tg-0pky"></td>
    <td class="tg-0pky">u1 = 0x43</td>
    <td class="tg-0pky"></td>
  </tr>
  <tr>
    <td class="tg-0pky">4</td>
    <td class="tg-0pky" rowspan="2">2 bytes</td>
    <td class="tg-0pky" rowspan="2">u2</td>
    <td class="tg-0pky" rowspan="2">HVMC version</td>
  </tr>
  <tr>
    <td class="tg-0pky">5</td>
  </tr>
  <tr>
    <td class="tg-0pky">6</td>
    <td class="tg-0pky" rowspan="2">2 bytes</td>
    <td class="tg-0pky" rowspan="2">u2</td>
    <td class="tg-0pky" rowspan="2">Constant pool length</td>
  </tr>
  <tr>
    <td class="tg-0pky">7</td>
  </tr>
  <tr>
    <td class="tg-0pky">8</td>
    <td class="tg-0pky" rowspan="4">cpsize</td>
    <td class="tg-0pky" rowspan="4">table</td>
    <td class="tg-0pky" rowspan="4">A list of constants, see <span style="font-style:italic">constant pool</span><span style="font-style:normal">.</span></td>
  </tr>
  <tr>
    <td class="tg-0pky">...</td>
  </tr>
  <tr>
    <td class="tg-0pky">...</td>
  </tr>
  <tr>
    <td class="tg-0pky">...</td>
  </tr>
  <tr>
    <td class="tg-0pky">cpsize + 8</td>
    <td class="tg-0pky">csize</td>
    <td class="tg-0pky">table</td>
    <td class="tg-0pky">A list of codes, see <span style="font-style:italic">code section.</span></td>
  </tr>
</tbody>
</table>

## Constant pool

| Constant Name | Total size | Startup byte | Followed bytes |
|:-------------:|:----------:|:------------:|:--------------:|
| Integer | 5 bytes | 0x00 | u1, u1, u1, u1 |

## Bytecode Instructions (Opcodes)

| Name | Opcode <br/> (in hex) | Followed bytes <br/> [count]: [operand labels] | Stack <br/> [before] -> [after] | Description |
|:----:|:---------------------:|:----------------------------------------------:|:-------------------------------:|:-----------:|
| CONST | 00 | 4: indexbyte1, indexbyte2, indexbyte3, indexbyte4 | → value | Loads a value from constant pool and push |
| CONST_0 | 01 | | → `false` aka 0 | Loads a `false` and push |
| CONST_1 | 02 | | → `true` aka 1 | Loads a `true` and push |
| CONST_NIL | 03 | | → `nil` aka 0 | Loads a `nil` and push |
| DUMP | 04 | | value → | Pop a value and print out |
| NEG | 05 | | value → result | Negate value |
| ADD | 06 | | value1, value2 → result | Add value1 and value2 |
| SUB | 07 | | value1, value2 → result | Subtract value1 and value2 |
| MUL | 08 | | value1, value2 → result | Multiply value1 and value2 |
| DIV | 09 | | value1, value2 → result | Divide value1 and value2 |
| REM | 0A | | value1, value2 → result | Mod value1 and value2 |

