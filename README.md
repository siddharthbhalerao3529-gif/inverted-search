# 🔍 Inverted Search Using Hash Algorithms
*A visual representation of an inverted index mapping words to files*


## 🚀 Overview
Inverted indexing is the backbone of **search engines** and **document retrieval systems**.  
This project implements an **inverted search system** in C using **hash algorithms**, which allows fast lookup of words across multiple files.  

It reads multiple text files, normalizes words, removes punctuation, and stores them in **hash-based buckets**. Each word is mapped to the **files it appears in and the number of occurrences**, enabling fast searches and efficient storage.  

**Purpose:** Learn and demonstrate **data structures, hashing, linked lists, and file handling in C**.

---

## ✨ Features
- ✅ Reads multiple text files and extracts words  
- ✅ Normalizes words to **lowercase** and removes punctuation  
- ✅ Uses **hash-based buckets** (A-Z) for fast access  
- ✅ Tracks **file occurrences** for each word  
- ✅ Skips already processed files to avoid duplication  
- ✅ Ensures **unique words per bucket**, updating counts if repeated  
- ✅ Provides **fast search queries** for words across files  
