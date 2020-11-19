# Blockchain 2 užduotis

# V0.2 versija

- Sugeneruoja 1000 vartotojų su random balansais
- Sugeneruoja 10000 transakcijų
- Transakcijos yra patikrinamos ar yra galimos
- Programa išrenka 100 transakcijų
- Randa naują bloką į kurį įdedama 100 išrinktų tranksakcijų
- Kasimo procesas vyksta tarp 5 blokų
- Išrenkamas vienas random blokas iš tų 5 ir duodama 100000 bandymų jį iškasti, jei nepavyksta, pereinama prie kito iš likusių blokų
- Blokų kasimo procesas vyksta kol pasibaigia 100 transakcijų
- Baigiant kasti bloką yra įvykdomos transakcijos

Dėl mano hash funkcijos prasto veikimo, kasimo procesas ieško ne nulių hash'o pradžioje, bet vieneto
