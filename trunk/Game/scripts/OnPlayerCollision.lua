-- OnPlayerCollision.lua
--- this file handles the events after collision with player

player:SetHp(player:GetHp() - 2)

if(player:GetHp() <= 0) then
	print("player died")
	player:SetHp(100)
end

print (player:GetHp())
--print(player:GetX());