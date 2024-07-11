void check_button()
{
  if(digitalRead(pullup_button))
  {


    if(counter >= max_turn_number || counter == 0 )
    {
      counter = 0;
      counter_job = 0;
      new_custom_turn_value_state = false;
      max_turn_number = 25;
      start_LED();
      display_start_screen();
    }

    if(counter > 0 && counter < max_turn_number)
    {
      max_turn_number = counter * 2;
      new_custom_turn_value_state = true;
      counter_job = counter_job -1; //for oled change
      blue_LED_signal();
    }

  }
}



void main_function()
{
    halotron_run();
    updateScreen();
    check_button();
    run_leds_show();
    delay(100);
}

