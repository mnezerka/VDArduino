<script>

  $( function() {
    $( ".program-op input:checkbox" ).checkboxradio();
  } );
  
  function checkLength( o, n, min, max ) {
    if ( o.val().length > max || o.val().length < min ) {
      o.addClass( "ui-state-error" );
      /*updateTips( "Length of " + n + " must be between " +
        min + " and " + max + "." );*/
      return false;
    } else {
      return true;
    }
  }

  function checkRegexp( o, regexp, n ) {
    if ( !( regexp.test( o.val() ) ) ) {
      o.addClass( "ui-state-error" );
      /*updateTips( n );*/
      return false;
    } else {
      return true;
    }
  }
  
  function reloadMe()
  {
    location.reload();       
  }

  function program_add() 
  {     
    var valid = true;
    var allFields = $( [] ).add( $("#add_title" ) ).add( $("#add_from_time" ) ).add( ("#add_to_time" ) );
    allFields.removeClass( "ui-state-error" );

    valid = valid && checkLength( $("#add_title"), "Název programu", 1, 50 );
    valid = valid && checkLength( $("#add_from_time"), "Čas od", 4, 5 );
    valid = valid && checkLength( $("#add_to_time"),   "Čas do", 4, 5 );

    if ( !valid ) return false;

    dialogAdd.dialog( "close" );

    $.ajax({
      method: "POST",
      url: "script/program_add.php",
      data: {
        title     : $("#add_title").val(),
        color     : $("#add_color").val(),
        priority  : $("#add_priority").val(),
        from_date : $("#add_from_date").val(),
        to_date   : $("#add_to_date").val(),
        from_time : $("#add_from_time").val(),
        to_time   : $("#add_to_time").val(),
        max       : $("#add_max").val(),
        min       : $("#add_min").val(),
        sun       : +$("#add_sun").is( ':checked' ),
        mon       : +$("#add_mon").is( ':checked' ),
        tue       : +$("#add_tue").is( ':checked' ),
        wed       : +$("#add_wed").is( ':checked' ),
        thu       : +$("#add_thu").is( ':checked' ),
        fri       : +$("#add_fri").is( ':checked' ),
        sat       : +$("#add_sat").is( ':checked' )
      }              
    })
      .done(function() { reloadMe(); });
  }
  
  function program_edit() 
  {     
    var valid = true;
    var allFields = $( [] ).add( $("#edit_title" ) ).add( $("#edit_from_time" ) ).add( ("#edit_to_time" ) );
    allFields.removeClass( "ui-state-error" );

    valid = valid && checkLength( $("#edit_title"), "Název programu", 1, 50 );
    valid = valid && checkLength( $("#edit_from_time"), "Čas od", 4, 5 );
    valid = valid && checkLength( $("#edit_to_time"),   "Čas do", 4, 5 );

    if ( !valid ) return false;
       
    dialogEdit.dialog( "close" );    

    $.ajax({
      method: "POST",
      url: "script/program_edit.php",
      data: {
        id        : $("#edit_id").val(),
        title     : $("#edit_title").val(),
        color     : $("#edit_color").val(),
        priority  : $("#edit_priority").val(),
        from_date : $("#edit_from_date").val(),
        to_date   : $("#edit_to_date").val(),
        from_time : $("#edit_from_time").val(),
        to_time   : $("#edit_to_time").val(),
        max       : $("#edit_max").val(),
        min       : $("#edit_min").val(),
        sun       : +$("#edit_sun").is( ':checked' ),
        mon       : +$("#edit_mon").is( ':checked' ),
        tue       : +$("#edit_tue").is( ':checked' ),
        wed       : +$("#edit_wed").is( ':checked' ),
        thu       : +$("#edit_thu").is( ':checked' ),
        fri       : +$("#edit_fri").is( ':checked' ),
        sat       : +$("#edit_sat").is( ':checked' )
      }              
    })
      .done(function() { reloadMe(); });
  }  
    
  function program_delete(id) 
  {     
    $.ajax({
      method: "POST",
      url: "script/program_delete.php",
      data: {
        id: id
      }              
    })
      .done(function() { reloadMe(); });    
  } 
  
  function program_export() 
  {     
    dialogExport.dialog( "close" );
    $.ajax({
      method: "POST",
      url: "script/program_export.php",
      data: {
        thermopass: $("#export_thermopass").val(),
      }              
    })
      .done(function(data) { 
        if (data === "!PASSWD") dialogError.dialog( "open" );
                           else dialogSuccess.dialog( "open" );
      });    
  }
  
  function program_import() 
  {     
    dialogImport.dialog( "close" );    
    $.ajax({
      method: "POST",
      url: "script/program_import.php",
      data: {}              
    })
      .done(function() { reloadMe(); });    
  }  
  
  $( function() {
    $( "#add_from_date" ).datepicker({
      dateFormat: "dd.mm.yy",
      monthNames: ['Leden','Únor','Březen','Duben','Květen','Červen','Červenec','Srpen','Září','Říjen','Listopad','Prosinec'],
      dayNamesMin: ['Ne','Po','Út','St','Čt','Pá','So'],
      firstDay: 1      
      });
    $( "#add_to_date" ).datepicker({
      dateFormat: "dd.mm.yy",
      monthNames: ['Leden','Únor','Březen','Duben','Květen','Červen','Červenec','Srpen','Září','Říjen','Listopad','Prosinec'],
      dayNamesMin: ['Ne','Po','Út','St','Čt','Pá','So'],
      firstDay: 1      
      });
    $( "#edit_from_date" ).datepicker({
      dateFormat: "dd.mm.yy",
      monthNames: ['Leden','Únor','Březen','Duben','Květen','Červen','Červenec','Srpen','Září','Říjen','Listopad','Prosinec'],
      dayNamesMin: ['Ne','Po','Út','St','Čt','Pá','So'],
      firstDay: 1      
      });
    $( "#edit_to_date" ).datepicker({
      dateFormat: "dd.mm.yy",
      monthNames: ['Leden','Únor','Březen','Duben','Květen','Červen','Červenec','Srpen','Září','Říjen','Listopad','Prosinec'],
      dayNamesMin: ['Ne','Po','Út','St','Čt','Pá','So'],
      firstDay: 1      
      });             
  } ); 
  
  dialogAdd = $( "#program-add" ).dialog({
    autoOpen: false,
    width: 600,
    modal: true,
    buttons: {
      "Přidat": program_add,
      "Zrušit": function() {
        dialogAdd.dialog( "close" );
      }
    },
  }); 
  
  dialogEdit = $( "#program-edit" ).dialog({
    autoOpen: false,
    width: 600,
    modal: true,
    buttons: {
      "Uložit": program_edit,
      "Zrušit": function() {
        dialogEdit.dialog( "close" );
      }
    },
  });  
  
  dialogExport = $( "#program-export" ).dialog({
    autoOpen: false,
    width: 600,
    modal: true,
    buttons: {
      "Přeprogramovat": program_export,
      "Zrušit": function() {
        dialogExport.dialog( "close" );
      }
    },
  });  

  dialogImport = $( "#program-import" ).dialog({
    autoOpen: false,
    width: 600,
    modal: true,
    buttons: {
      "Importovat": program_import,
      "Zrušit": function() {
        dialogImport.dialog( "close" );
      }
    },
  });
   
  dialogError = $( "#program-error" ).dialog({
    width: 400,    
    autoOpen: false,
    modal: true,
    buttons: {
      "Zavřít": function() {
        dialogError.dialog( "close" );
        $( "#export_thermopass" ).val("");
      }
    },
  });
  
  dialogSuccess = $( "#program-success" ).dialog({
    width: 400,
    autoOpen: false,
    modal: true,
    buttons: {
      "Zavřít": function() {
        dialogSuccess.dialog( "close" );
      }
    },
  });    

</script>
<?php

  //Include
  include "class/Config.class.php";
  include "class/Database.class.php";
  include "class/Program.class.php";
  include "class/Params.class.php";
  Params::get();

  //Database
  $database = new Database();
  $database->connect();

  //Objects
  $programSet = Program::loadAllEditable($database);  
    
  //Display
  print '<p>Veškeré změny v programech se projeví až po jejich odeslání do termostatu. Nižší číslo priority má přednost.</p>';
  print '<table id="program" class="default">';
  print '<tr>';
    print '<th>Program & priorita</th>';
    print '<th class="period">Období</th>';
    print '<th class="time">Čas</th>';
    print '<th class="small">Po</th>';
    print '<th class="small">Út</th>';
    print '<th class="small">St</th>';
    print '<th class="small">Čt</th>';
    print '<th class="small">Pá</th>';
    print '<th class="small">So</th>';
    print '<th class="small">Ne</th>';
    print '<th class="temp">Teplota</th>';
    print '<th class="hyst">Hystereze</th>';
    print '<th class="but">Upravit & odebrat</th>';
  print '</tr>';
  
  foreach($programSet as $program)
  {
    if ($program->priority != Program::PRIORITY_LOW && $program->priority != Program::PRIORITY_OFF && $program->priority != Program::PRIORITY_ON)
      print '<tr>';
    else
      print '<tr class="manual">';
      
      print '<td>';
        if (defined('Program::'. $program->color))
          $color = constant('Program::'. $program->color);
        else
          $color = Program::GREY; 
        print '<div class="floatleft vert2 colorbox-prog" style="background-color: '. $color. '">'. $program->priority.'</div>';        
        print $program->title;
      print '</td>';
      
      print '<td class="period">';
        if ($program->from_date != '' && $program->to_date != '')
        {
           $date_from = new DateTime($program->from_date);          
           $date_to   = new DateTime($program->to_date);
           print '<b>'. $date_from->format('d.m.Y'). '</b> '. $date_to->format('d.m.Y');              
        }
        else print '✖';
      print '</td>';
               
      print '<td class="time">';
        print '<b>'.substr($program->from_time, 0, 5).'</b>';
        print '<br />';
        print substr($program->to_time, 0, 5);
      print '</td>';
      
      if (Params::$date->format("w") == 1) $class = 'orange'; else $class = 'black';
      print '<td class="small">'; if ($program->mon) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';
      if (Params::$date->format("w") == 2) $class = 'orange'; else $class = 'black';
      print '<td class="small">'; if ($program->tue) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';
      if (Params::$date->format("w") == 3) $class = 'orange'; else $class = 'black';
      print '<td class="small">'; if ($program->wed) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';
      if (Params::$date->format("w") == 4) $class = 'orange'; else $class = 'black';
      print '<td class="small">'; if ($program->thu) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';
      if (Params::$date->format("w") == 5) $class = 'orange'; else $class = 'black';
      print '<td class="small">'; if ($program->fri) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';      
      if (Params::$date->format("w") == 6) $class = 'orange'; else $class = 'black';
      print '<td class="small">'; if ($program->sat) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';
      if (Params::$date->format("w") == 0) $class = 'orange'; else $class = 'black';   
      print '<td class="small">'; if ($program->sun) print "<span class='$class'>✔</span>"; else print '<span class="grey">❖</span>'; print '</td>';
      
      if ($program->min != '' && $program->max != '')
      {
        print '<td class="temp" style="color:'.$color.'"><b>'. $program->max. '</b> °C</td>';
        print '<td class="hyst">'. $program->min. ' °C</td>';
      }
      else print '<td colspan="2" class="border-right"><i>vytápění vypnuto<i></td>';
      
      if ($program->priority != Program::PRIORITY_LOW && $program->priority != Program::PRIORITY_OFF && $program->priority != Program::PRIORITY_ON)
      {
        print '<td class="but" class="noborder-right">';
          print '<button onclick="';
            print '$(\'#edit_id\').val(\''. $program->id. '\');';
            print '$(\'#edit_title\').val(\''. $program->title. '\');';
            print '$(\'#edit_color\').val(\''. $program->color. '\');';
            print '$(\'#edit_priority\').val(\''. $program->priority. '\');';              
            if ($program->from_date != '' && $program->to_date != '')
            {
              print '$(\'#edit_from_date\').val(\''. $date_from->format('d.m.Y'). '\');';
              print '$(\'#edit_to_date\').val(\''. $date_to->format('d.m.Y'). '\');';       
            }
            else
            {
              print '$(\'#edit_from_date\').val(\'\');';
              print '$(\'#edit_to_date\').val(\'\');';                     
            }
            print '$(\'#edit_from_time\').val(\''. substr($program->from_time, 0, 5). '\');';
            print '$(\'#edit_to_time\').val(\''. substr($program->to_time, 0, 5). '\');';
            print '$(\'#edit_max\').val(\''. $program->max. '\');';
            print '$(\'#edit_min\').val(\''. $program->min. '\');';
            print '$(\'#edit_sun\').prop(\'checked\','. $program->sun. ').checkboxradio(\'refresh\');';
            print '$(\'#edit_mon\').prop(\'checked\','. $program->mon. ').checkboxradio(\'refresh\');';
            print '$(\'#edit_tue\').prop(\'checked\','. $program->tue. ').checkboxradio(\'refresh\');';
            print '$(\'#edit_wed\').prop(\'checked\','. $program->wed. ').checkboxradio(\'refresh\');';
            print '$(\'#edit_thu\').prop(\'checked\','. $program->thu. ').checkboxradio(\'refresh\');';
            print '$(\'#edit_fri\').prop(\'checked\','. $program->fri. ').checkboxradio(\'refresh\');';
            print '$(\'#edit_sat\').prop(\'checked\','. $program->sat. ').checkboxradio(\'refresh\');';        
          print '" class="program-edit-button ui-button ui-widget ui-corner-all">✎</button> ';
          print '<button onclick="program_delete('. $program->id. ')" class="ui-button ui-widget ui-corner-all">❌ </button>';
        print '</td>';      
      }
      
    print '</tr>';
  }
  print '</table>';
?>

<p>

<button id="program-add-button" class="ui-button ui-widget ui-corner-all">➕ Přidat nový program</button>
<button id="program-import-button" class="ui-button ui-widget ui-corner-all">♻ Importovat programy z termostatu</button>

<br /><br />
</p>

<hr />

<p>Pro odeslání programů do termostatu je třeba uvést kontrolní heslo:</p>

<p>
  <input class="input-passwd ui-button ui-widget ui-corner-all" id="export_thermopass" type="password" placeholder="Heslo" />
  <button class="ui-button ui-widget ui-corner-all" id="program-export-button">➽ Přeprogramovat termostat</button>
</p>

<!-- ADD ---------------------------------------------------------------------->

<div id="program-add" title="➕ Přidat nový program">
  <p class="validateTips">
    Datum nevyplňujte, pokud program nemá mít omezení. Neuvedení teploty znamená, že topení zůstane vypnuté.
    Datum od musí předcházet datum do. Stejně tak je to s časem. Teplota vytápění musí být vyšší než teplota minimální.
  </p>
  
  <form action=''>
    <fieldset class="program-op">

      <label for="add_title" class="standard">Název programu</label>
        <input required="true" type="text" name="title" id="add_title" value="">

      <label for="add_color" class="standard">Barva</label>
        <select type="text" name="color" id="add_color">
          <option value="BLUE">Modrá</option>
          <option value="GREEN">Zelená</option>
          <option value="YELLOW">Žlutá</option>
          <option value="RED">Červená</option>            
        </select>

      <label for="add_priority" class="standard">Priorita</label>
        <select type="text" name="priority" id="add_priority">
          <option value="5">5 (nejnižší)</option>
          <option value="4">4 (nízká)</option>
          <option value="3">3 (střední)</option>
          <option value="2">2 (vysoká)</option>            
          <option value="1">1 (nejvyšší)</option>            
        </select>

      <label for="add_from_date" class="standard">Datum od/do</label>
        <input type="text" class="date" name="from_date" id="add_from_date">
      &mdash;
        <input type="text" class="date" name="to_date" id="add_to_date">

      <label for="add_from_time" class="standard">Čas od/do a dny týdne</label>
        <input required="true" type="time" name="from_time" id="add_from_time" value="00:00">
      &mdash;
        <input required="true" type="time" name="to_time" id="add_to_time" value="23:59">        
        
      <label for="add_mon" class="checkbox">Po</label>
        <input type="checkbox" name="mon" id="add_mon" value="1">
      <label for="add_tue" class="checkbox">Út</label>
        <input type="checkbox" name="tue" id="add_tue" value="1">
      <label for="add_wed" class="checkbox">St</label>
        <input type="checkbox" name="wed" id="add_wed" value="1">
      <label for="add_thu" class="checkbox">Čt</label>
        <input type="checkbox" name="thu" id="add_thu" value="1">
      <label for="add_fri" class="checkbox">Pá</label>
        <input type="checkbox" name="fri" id="add_fri" value="1">
      <label for="add_sat" class="checkbox">So</label>
        <input type="checkbox" name="sat" id="add_sat" value="1">      
      <label for="add_sun" class="checkbox">Ne</label>
        <input type="checkbox" name="sun" id="add_sun" value="1">
        
      <label for="add_max" class="standard">Teplota vytápění [°C]</label>
        <input type="number" name="max" id="add_max" value="" min="-50" max="50" step="0.1">
      <label for="add_min" class="standard">Minimální teplota [°C]</label>
        <input type="number" name="min" id="add_min" value="" min="-50" max="50" step="0.1">                      
        
      <!-- Allow form submission with keyboard without duplicating the dialog button -->
      <input type="submit" tabindex="-1" class="invisible">
          
    </fieldset>
  </form>
</div>

<!-- EDIT --------------------------------------------------------------------->

<div id="program-edit" title="✎ Upravit stávající program">
  <p class="validateTips">
    Datum nevyplňujte, pokud program nemá mít omezení. Neuvedení teploty znamená, že topení zůstane vypnuté.
    Datum od musí předcházet datum do. Stejně tak je to s časem. Teplota vytápění musí být vyšší než teplota minimální.
  </p>
  
  <form action=''>
    <fieldset class="program-op">
    
        <input type="hidden" name="id" id="edit_id" value="">    

      <label for="edit_title" class="standard">Název programu</label>
        <input required="true" type="text" name="title" id="edit_title" value="">

      <label for="edit_color" class="standard">Barva</label>
        <select type="text" name="color" id="edit_color">
          <option value="BLUE">Modrá</option>
          <option value="GREEN">Zelená</option>
          <option value="YELLOW">Žlutá</option>
          <option value="RED">Červená</option>            
        </select>

      <label for="edit_priority" class="standard">Priorita</label>
        <select type="text" name="priority" id="edit_priority">
          <option value="5">5 (nejnižší)</option>
          <option value="4">4 (nízká)</option>
          <option value="3">3 (střední)</option>
          <option value="2">2 (vysoká)</option>            
          <option value="1">1 (nejvyšší)</option>            
        </select>

      <label for="edit_from_date" class="standard">Datum od/do</label>
        <input type="text" class="date" name="from_date" id="edit_from_date">
      &mdash;
        <input type="text" class="date" name="to_date" id="edit_to_date">

      <label for="edit_from_time" class="standard">Čas od/do a dny týdne</label>
        <input required="true" type="time" name="from_time" id="edit_from_time" value="00:00">
      &mdash;
        <input required="true" type="time" name="to_time" id="edit_to_time" value="23:59">        
        
      <label for="edit_mon" class="checkbox">Po</label>
        <input type="checkbox" name="mon" id="edit_mon" value="1">
      <label for="edit_tue" class="checkbox">Út</label>
        <input type="checkbox" name="tue" id="edit_tue" value="1">
      <label for="edit_wed" class="checkbox">St</label>
        <input type="checkbox" name="wed" id="edit_wed" value="1">
      <label for="edit_thu" class="checkbox">Čt</label>
        <input type="checkbox" name="thu" id="edit_thu" value="1">
      <label for="edit_fri" class="checkbox">Pá</label>
        <input type="checkbox" name="fri" id="edit_fri" value="1">
      <label for="edit_sat" class="checkbox">So</label>
        <input type="checkbox" name="sat" id="edit_sat" value="1">      
      <label for="edit_sun" class="checkbox">Ne</label>
        <input type="checkbox" name="sun" id="edit_sun" value="1">
        
      <label for="edit_max" class="standard">Teplota vytápění [°C]</label>
        <input type="number" name="max" id="edit_max" value="" min="-50" max="50" step="0.1">
      <label for="edit_min" class="standard">Minimální teplota [°C]</label>
        <input type="number" name="min" id="edit_min" value="" min="-50" max="50" step="0.1">                      
        
      <!-- Allow form submission with keyboard without duplicating the dialog button -->
      <input type="submit" tabindex="-1" class="invisible">
   
    </fieldset>
  </form>
</div>

<!-- EXPORT ------------------------------------------------------------------->

<div id="program-export" title="➽ Přeprogramovat termostat">
  <p></span>Opravdu chcete přeprogramovat termostat?</p>
</div>

<!-- IMPORT ------------------------------------------------------------------->

<div id="program-import" title="♻ Importovat programy">
  <p>Opravdu chcete přemazat zobrané programy importem z termostatu?</p>
</div>

<!-- ERROR -------------------------------------------------------------------->

<div id="program-error" title="⛔ Chyba">
  <p>Bylo zadáno špatné heslo!</p>
</div>

<!-- SUCCESS ------------------------------------------------------------------>

<div id="program-success" title="✔ Výsledek">
  <p>Termostat byl úspěšně přeprogramován</p>
</div>

<!-- END ---------------------------------------------------------------------->

<script>
    $( "#program-add-button" ).button().on( "click", function() {
      dialogAdd.dialog( "open" );
    }); 
    $( ".program-edit-button" ).button().on( "click", function() {
      dialogEdit.dialog( "open" );
    }); 
    $( "#program-export-button" ).button().on( "click", function() {
      dialogExport.dialog( "open" );
    });
    $( "#program-import-button" ).button().on( "click", function() {
      dialogImport.dialog( "open" );
    });           
</script>