boards are done

1 gateway board for concentrator module, featuring a female sma connector and extra debug holes for esp32

3 transciever boards for different type of lora packets


//update

changed the footprints for 10uf caps for convinience. kart daha f/p olsun diye footprint değiştirdim amk. cebime 150 lira kaldı. also removed debug pinholes on the gateway card because somehow they lost their reference values, so script wouldnt autoroute them.
only transciever 3 is updated with the new footprint, since we willl only use that one.


--possible improvements
instead of through hole lora components, solder the chips directly onto board for production. also could find esp32 dev modules without presoldered pins and do the same
