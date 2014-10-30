library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity test_ram is
    port(clk, rst, enable, R_W: in std_logic;
         addr, data_in: in std_logic_vector(31 downto 0);
         data_out: out std_logic_vector(31 downto 0));
end test_ram;

architecture bhv of test_ram is
    type memory is array (0 to 255) of std_logic_vector(31 downto 0); 
    signal regs: memory ;

begin
    process(clk, enable, R_W, addr)
    begin
        if (rst='1') then
            regs(0)<= "00000000100000000000000000010000"; --lw 0,0,16
            regs(1)<= "00000000100000010000000000010001"; --lw 0,1,17
            regs(2)<= "00000000100000100000000000010010"; --lw 0,2,18
            regs(3)<= "00000000100000110000000000010011"; --lw 0,3,19
            regs(4)<= "00000000100001000000000000010100"; --lw 0,4,20
            regs(5)<= "00000000100001010000000000010101"; --lw 0,5,21
            regs(6)<= "00000000100001100000000000010110"; --lw 0,6,22
            regs(7)<= "00000000100001110000000000010111"; --lw 0,7,23
            regs(8)<= "00000000000000010000000000000000"; --add 0,1,0
            regs(9)<= "00000000000000100000000000000000"; --add 0,2,0
            regs(10)<= "00000000000000110000000000000000"; --add 0,3,0
            regs(11)<= "00000000000001000000000000000000"; --add 0,4,0
            regs(12)<= "00000000000001010000000000000000"; --add 0,5,0
            regs(13)<= "00000000000001100000000000000000"; --add 0,6,0
            regs(14)<= "00000000000001110000000000000000"; --add 0,7,0
            regs(15)<= "00000001100000001111110100000000"; --halt
            regs(16)<= "00000000000000000000000000000000"; -- 16:0
            regs(17)<= "00000000000000000000000000000001"; 
            regs(18)<= "00000000000000000000000000000010"; -- 2
            regs(19)<= "00000000000000000000000000000011";
            regs(20)<= "00000000000000000000000000000100";
            regs(21)<= "00000000000000000000000000000101";
            regs(22)<= "00000000000000000000000000000110";
            regs(23)<= "00000000000000000000000000000111";
            regs(24)<= "00000000000000000000000000001000"; -- 8
            regs(25)<= "00000000000000000000000000001000"; -- 8

        elsif (enable = '1') then
            if (R_W = '0') then
                data_out <= regs(conv_integer(addr));
            elsif (clk'event and clk = '1') then
                regs(conv_integer(addr)) <=  data_in;
            end if;
        end if;
    end process;
end bhv;
