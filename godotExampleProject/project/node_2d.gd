extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var a = GodotSummator.new();
	print(a.add(1,2));
	print(a.wrongAdd(1,2));
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
