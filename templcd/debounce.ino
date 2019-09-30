

void btnde()
{
    byte btn1Before = digitalRead(7);
    byte btn2Before = digitalRead(8);

    delay(250); // Wait 50 ms, or 100 depending on your debouncing time

    byte btn1After = digitalRead(7);
    byte btn2After = digitalRead(8);

    if ((btn1Before == HIGH) && (btn1After == LOW))
    {
       btn[1] = true;
    } 
    else if ((btn2Before == HIGH) && (btn2After == LOW))
    {
       btn[2] = true;
    } 
}
