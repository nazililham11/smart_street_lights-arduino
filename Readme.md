# Smart Street Lights

Alat ini diciptakan untuk memberikan kontribusi dan solusi pada pemerintah terkait permasalahan konsumsi listrik pada PJU yang relatif besar, apabila alat ini diterapkan, tentu akan menghemat konsumsi listrik yang dihabiskan oleh PJU. Dengan mengurangi konsumsi llistrik, secara tidak langsung juga mengurangi pembuangan gas emisi yang dihasilkan dari bahan fosil yang mana merupakan bahan bakar yang paling banyak digunakan sebagai pembangkit listrik PLN. Selain itu, penggunaan photovoltaik yang ramah lingkungan mendukung energi terbarukan yang selama ini digencarkan. 

## Komponen
 - Acrylic
 - Solar Panel 5v
 - Arduino
 - Sensor Ultrasonic
 - Mosfet IRF3205
 - LED 
 - Modul Stepup ke 5v
 - Modul Charger
 - Batterai 18650
 - Saklar
 - Kabel


## Sistem Kerja Alat
![Ilustrasi](Assets/Ilustrasi.png)
1.	Keadaan lampu akan menyala redup ketika tidak ada objek datang di zona deteksi sensor ultrasonic
2.	Ketika mobil masuk dalam zona deteksi, lampu LED otomatis menyala terang, didukung dengan 2 buah  sensor ultrasonic untuk mendeteksi dua arah berlawanan zona deteksi dapat diatur jaraknya sesuai kebutuhan.
3.	Ketika mobil lepas dari zona deteksi lampu kembali menyala redup
4.	Pada penerapannya, zona deteksi diatur jaraknya sedemikian rupa agar tidak membahayakan pengendara yang melaju cepat (lampu harus menyala terang beberapa detik sebelum kendaraan lewat sehingga tidak mengganggu penglihatan pengendara)


## Konfigurasi Alat
**Posisi Jumper**
<br><img src="Assets/Device%20(8).jpg" width="350">


**Konfigurasi Jumper**
<br><img src="Assets/SettingJumper.png" width="400">


## Foto Alat
<img src="Assets/Device%20(1).jpg" width="350">
<img src="Assets/Device%20(2).jpg" width="350">
<img src="Assets/Device%20(3).jpg" width="350">
<img src="Assets/Device%20(4).jpg" width="350">
<img src="Assets/Device%20(5).jpg" width="350">
<img src="Assets/Device%20(6).jpg" width="350">
<img src="Assets/Device%20(7).jpg" width="350">
<img src="Assets/Device%20(9).jpg" width="350">
<img src="Assets/Device%20(10).jpg" width="350">
<img src="Assets/Device%20(11).jpg" width="350">
<img src="Assets/Device%20(12).jpg" width="350">
<img src="Assets/Device%20(13).jpg" width="350">
<img src="Assets/Device%20(14).jpg" width="350">
<img src="Assets/Device%20(15).jpg" width="350">
<img src="Assets/Device%20(17).jpg" width="350">


## Box Acrylic
Box Acrylic didesain dalam bentuk 3D ([Uncomplete 3D Design.skp](https://github.com/nazililham11/smart_street_lights-arduino/blob/a32a4c9f92976d29509b6a7dd917555c43372e27/Assets/Uncomplete%203D%20Design.skp)) untuk menentukan desain, sistem penguncian (untuk bongkar/pasang acrylic), tata letak, dan posisi dari hardware.

![Desain 3D](Assets/desain-3d-1.png)
![Desain 3D](Assets/desain-3d-2.png)
![Desain 3D](Assets/desain-3d-3.png)


 Setelah desain 3D telah dibuat kemudian dibuat versi cutting acrylic ([acrylic.cdr](https://github.com/nazililham11/measurement_tool/raw/master/Assets/acrylic.cdr)) menggunakan aplikasi corel draw. Acrylic yang digunakan yaitu acrylic dengan tebal 2mm berwarna bening dan hitam.
![Desain 3D](Assets/desain-acrylic.png) 
Kuning pada desain menunjukan acrylic bening dan merah menunjukan acrylic hitam.
