**📌 Project Overview:**
This project implements **Least Significant Bit (LSB) Image Steganography** to hide a secret message within a `.bmp` or `.png` image file. Steganography is a technique of **concealing information** within files, making it valuable for **covert data transmission** in areas such as military, intelligence, and secure communication.

---

**🛠️ What is Steganography?**
Steganography is the practice of **hiding data within another medium**. This project utilizes **digital steganography**, where the message is embedded in the **Least Significant Bits (LSB)** of an image's pixel data. Since **only LSBs are altered**, the image quality remains visually unchanged, ensuring **discreet data embedding**.

---

**🔍 Why Use Steganography?**
✔ Hide Secret Credentials  
✔ Prevent Data Forgery  
✔ Enable Secure Message Passing  

**📌 Applications of Steganography:**
🔹 **Military Communications**  
🔹 **Intelligence Agencies**  
🔹 **Medical Imaging**  
🔹 **Internet Banking**  
🔹 **Secure Online Elections**  

---

**🖼️ BMP Image Format & Pixel Structure:**

📌 **BMP File Structure:**
- A **54-byte header**, followed by **RGB pixel data**, making BMP suitable for LSB embedding.

📌 **Pixel Structure:**
- Each **pixel** in BMP images consists of **RGB values**.
- Modifying the **LSB** of these values results in minimal visual change, making BMP a **preferred format** for LSB steganography.

---

**🔢 How LSB Image Steganography Works:**
- The secret data is **encoded bit-by-bit** into the **LSB** of each pixel in a BMP file.
- During **decoding**, these bits are extracted to **reconstruct the hidden message**.

---

**🚀 Features:**
✔ **Encoding** – Hides a secret text file within an image file.  
✔ **Decoding** – Retrieves the hidden message from an encoded image.  
✔ **Error Handling** – Verifies file formats and checks for capacity limitations before encoding.  

---

**💻 Usage Instructions:**

📌 **Command-Line Interface**

➡️ **Encoding a Message:**  
```bash
./lsb_steg -e <image.bmp> <secret.txt> [output_file]
```
📝 **Parameters:**  
- `<image.bmp>` – BMP image to hide the secret.
- `<secret.txt>` – Text file containing the secret message.
- `[output_file]` – *(Optional)* Output file name *(Default: steged_img.bmp)*.

➡️ **Decoding a Message:**  
```bash
./lsb_steg -d <encoded_image.bmp> [output_file]
```
📝 **Parameters:**  
- `<encoded_image.bmp>` – BMP image with the hidden message.
- `[output_file]` – *(Optional)* Output file for decoded message *(Default: decoded.txt)*.

---

**📌 Example Usage:**

🔹 **Encoding:**  
```bash
./lsb_steg -e original.bmp secret.txt steged_img.bmp
```
🔹 **Decoding:**  
```bash
./lsb_steg -d steged_img.bmp decoded.txt
```

---

**⚙️ Design Overview:**

📌 **Encoding Process:**
1️⃣ **Check Image Capacity** – Verifies if the image has enough capacity to store the message.  
2️⃣ **Embed Magic String** – Adds a unique identifier (`#*`) to detect hidden data.  
3️⃣ **Encode Metadata** – Stores file extension and message size.  
4️⃣ **Embed Message** – Hides the actual message **bit-by-bit**.  
5️⃣ **Save Encoded Image** – Outputs a new image file with the embedded message.  

📌 **Decoding Process:**
1️⃣ **Verify Magic String** – Confirms the presence of hidden data.  
2️⃣ **Extract Metadata** – Reads the **file extension** and **message size**.  
3️⃣ **Retrieve Message** – Decodes the **hidden message** bit-by-bit.  
4️⃣ **Save Decoded Message** – Outputs the **hidden message** as a text file.  

---

**⚠️ Error Handling:**
📌 The program provides **error messages** if:  
❌ The **image file lacks the required capacity** to embed the message.  
❌ **Incorrect file formats** are provided for encoding or decoding.  

---

**📚 References:**
📌 [Wikipedia – Steganography](https://en.wikipedia.org/wiki/Steganography)  
📌 [Wikipedia – Pixel](https://en.wikipedia.org/wiki/Pixel)  
📌 [BMP File Structure](https://en.wikipedia.org/wiki/BMP_file_format)  

---

✅ **This project is an efficient way to implement secure steganography using LSB techniques while maintaining the image quality and ensuring message confidentiality.**

