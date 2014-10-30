library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity ALU is
   port(a, b: in std_logic_vector(31 downto 0);
        s: in std_logic;
        o: out std_logic_vector(31 downto 0);
		eq: out std_logic);
end ALU;

architecture bhv of ALU is
begin
    process(a, b, s)
    begin
        case s is 
            when '0' =>
                o <= a + b;
            when '1' =>
                o <= not (a and b);
            when others =>
                null;
        end case;

        if (a = b) then
            eq <= '1';
        else
            eq <= '0'; 
        end if;
    end process;
end bhv;
