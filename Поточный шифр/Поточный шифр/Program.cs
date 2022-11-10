﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace StreamСipherOnHashAndCTRMode
{
    class Program
    {
        static void Main(string[] args)
        {
            var encoding = Encoding.GetEncoding(1251);


            var plainText = encoding.GetBytes("1111111111111111111111111111111111111111111111111111");
            var key = encoding.GetBytes("1123456");

            var nonce = new byte[4];
            using (var randomGenerator = new RNGCryptoServiceProvider())
                randomGenerator.GetBytes(nonce);

            // шифрование: ключ XOR или открытый текст
            var cipherText =
                nonce.Concat(
                    XorCounterModeEncryptDecrypt(key, nonce, plainText)
                );

            // расшифровать: ключ XOR или зашифрованный текст
            var decrypted = XorCounterModeEncryptDecrypt(
                keyBytes: key,
                nonceBytes: cipherText.Take(4).ToArray(),
                data: cipherText.Skip(4));

            var decryptedStr = encoding.GetString(decrypted.ToArray());

        }

        /// <summary>
        /// Потоковый шифр
        /// </summary>
        private static IEnumerable<byte> XorCounterModeEncryptDecrypt(byte[] keyBytes, byte[] nonceBytes, IEnumerable<byte> data)
        {
            if (keyBytes == null) throw new ArgumentNullException(nameof(keyBytes));
            if (data == null) throw new ArgumentNullException(nameof(data));
            if (nonceBytes == null) throw new ArgumentNullException(nameof(nonceBytes));
            if (nonceBytes.Length < 4) throw new ArgumentOutOfRangeException(nameof(nonceBytes));

            int roundIndex = 0;
            byte[] roundGamma = null;
            int gammaIndex = 0;
            foreach (var d in data)
            {
                if (gammaIndex == 0)
                {
                    // создать гамму

                    // создать блок счетчика: Одноразовый номер + счетчик
                    // другой способ: Счетчик Nonce XOR (имеет некоторые ограничения)
                    var counterBlock = nonceBytes.Concat(BitConverter.GetBytes(roundIndex)).ToArray();
                    using (var hmacSHA = new HMACSHA512(keyBytes))
                        roundGamma = hmacSHA.ComputeHash(counterBlock);

                }

                yield return (byte)(d ^ roundGamma[gammaIndex]);

                if (gammaIndex < roundGamma.Length - 1)
                    gammaIndex++;
                else
                {
                    gammaIndex = 0;
                    roundIndex++;


                }
            }
        }
    }
}
