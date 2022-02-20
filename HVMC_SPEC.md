# HVMC (Hieroglyph VM class file) Spec

## File Format

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
</style>
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
|:-:|:-:|:-:|:-:|
| Integer | 5 bytes | 0x00 | u1, u1, u1, u1 |
