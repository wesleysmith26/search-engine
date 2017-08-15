# Search Engine User Manual
###### By Charlie Barnes, Zach Bubrosky, and Wesley Smith

Step 1: Launch program by entering ./a.out /*document_title*/ into the command line

Step 2:
- The user (You!) will be prompted to select which mode they would like to enter. They can choose **Maintenance Mode** by entering 1 or **Interactive Mode** by entering 2

  ##### Maintenance Mode:
  - The user will be prompted to add a document (enter 1), clear the indexes (enter 2), or exit Maintenance Mode
    - **Add Document** - the user will enter the document name that they wish to add
    - **Clear Indexes** - both the AVL Tree and Hash Table will be cleared
    - **Exit Maintenance Mode** - the user will be returned to the start screen
    
  ##### Interactive Mode:
  - The user will be prompted to select the query processor by entering 1 or the search engine statistics (total page numbers indexed and total number of words indexed) by entering 2
    - **Query Processor:**
      - The user will enter a simple prefix Boolean query
      - **Format:**  
              * Single word - term  
              * AND - AND term 1, term 2, term 3 ... term n  
              * OR - Or term 1, term 2, term 3 ... term n  
              * NOT - AND/OR term 1, term 2, term 3 ... term n NOT term n-1, term n-2, term n-3 ... term n-x  
              **number of terms will be decided by the user**
      - **Boolean Definitions:**  
              * AND - will include page numbers shared by the following terms  
              * OR - will include all page numbers from the following terms  
              * NOT - will remove page numbers that the following terms appear on  
      - **Query Examples:**  
              * apple (one word search that will return all documents containing apple)  
              * AND apple banana (will return all documents containing both apple and banana)  
              * OR apple banana (will return all documents containing apple as well as documents containing banana)  
              * apple NOT banana (will return all documents containing apple that do not contain banana)  
              * AND apple (OR tree bush) banana (will return all documents containing apple, tree/bush, and banana)  
      - **Restrictions:** Levels of nest may not exceed two levels (i.e. two sets of parentheses), example above shows one level of nesting
      - **Display:**  
              * Data obtained from Boolean query search will be displayed in the following format:  
      (Page Number) (Frequency) (Page Title) (Date Article was Made) (Username of Article Author)  
  - The user will then be asked if they want to see the contents of a page in the results by entering y (yes) or n (no)
     - **If user enters yes:**  
       - The user will be prompted to enter a specific page number that they desire to view
       - The text from the page will be outputted
       - Then the user will be prompted to enter another page (enter specific page number) or exit back to start screen (enter -1)  
     - **If user enters no:**  
       - The user will be returned to the start screen  
       
We hope you enjoy using our search engine!
