--8x32 register
LIBRARY IEEE;
use IEEE.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity register_file is
    port(clk, rst, WR_enable: in std_logic;
         WR_address, RD1_address, RD2_address: in std_logic_vector(2 downto 0);
         data_in: in std_logic_vector(31 downto 0);
         RD1_out, RD2_out: out std_logic_vector(31 downto 0));
end register_file;

architecture bhv of register_file is
    type memory is array (0 to 7) of std_logic_vector(31 downto 0);
    signal reg: memory;

begin	
    read: process(clk, RD1_address, RD2_address)
    begin 
        if(clk = '1') then
            RD1_out <= reg(conv_integer(RD1_address));
            RD2_out <= reg(conv_integer(RD2_address));
        end if;
    end process	;

    write: process(clk, WR_enable, WR_address, data_in)
    begin
        if rst = '1' then		
            reg <= (0 => "00000000000000000000000000000000",
                   others => "00000000000000000000000000000000");
        else
            if(clk = '1') then
                if(WR_enable = '1') then
                    reg(conv_integer(WR_address)) <= data_in;
                end if;
            end if;
        end if;
    end process;
end bhv; 
