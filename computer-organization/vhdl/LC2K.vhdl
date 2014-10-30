library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity LC2K is
    port(clk, rst: in std_logic;
         outPC, outMem, outIR, outRF1, outRF2, inALU1, inALU2, outALU, outp: out std_logic_vector(31 downto 0));
end LC2K;

architecture bhv of LC2K is

    component ALU
        port(a, b: in std_logic_vector(31 downto 0);
             s: in std_logic;
             o: out std_logic_vector(31 downto 0);
             eq: out std_logic);
    end component;

    component mux2r
        port(a, b: in std_logic_vector(2 downto 0); 
             s: in std_logic;
             o: out std_logic_vector(2 downto 0));
    end component;

    component mux2
        port(a, b: in std_logic_vector(31 downto 0);
             s: in std_logic;
             o: out std_logic_vector(31 downto 0));
    end component;

    component mux4
        port(c, f: in std_logic_vector(31 downto 0);
             s: in std_logic_vector(1 downto 0);
             o: out std_logic_vector(31 downto 0));
    end component;

    component reg
        port(clk, rst, enable: in std_logic;
             data: in std_logic_vector(31 downto 0); 
             o: out std_logic_vector(31 downto 0));
    end component;

    component regbuf
        port(clk, enable: in std_logic; 
             data: in std_logic_vector(31 downto 0); 
             o: out std_logic_vector(31 downto 0));
    end component;

    component register_file
        port(clk, rst, WR_enable: in std_logic;
             WR_address, RD1_address, RD2_address: in std_logic_vector(2 downto 0);
             data_in: in std_logic_vector(31 downto 0);
             RD1_out, RD2_out: out std_logic_vector(31 downto 0));
    end component;

    component sext
        port(a: in std_logic_vector(15 downto 0);
             o: out std_logic_vector(31 downto 0));
    end component;

    component test_ram
        port(clk, rst, enable, R_W: in std_logic;
             addr, data_in: in std_logic_vector(31 downto 0);
             data_out: out std_logic_vector(31 downto 0));
    end component;

    component FSM
        port(clk, rst, ALU_eq: in std_logic;
             op: in std_logic_vector(2 downto 0);
             PC_en, Mem_mux, Mem_en, Mem_rw, IR_en, Dest_mux, RData_mux, Reg_en, ALU_mux1, ALU_op: out std_logic;
             ALU_mux2: out std_logic_vector(1 downto 0));
    end component;

    signal PCout: std_logic_vector(31 downto 0);
    signal ALUresult: std_logic_vector(31 downto 0);
    signal PCen: std_logic;

    signal ADDRout: std_logic_vector(31 downto 0);
    signal ADDRmux: std_logic;

    signal REGout: std_logic_vector(31 downto 0);
    signal RAMout: std_logic_vector(31 downto 0);
    signal MEMen: std_logic;
    signal RW: std_logic;

    signal IRout: std_logic_vector(31 downto 0);
    signal IRen: std_logic;

    signal REGW: std_logic_vector(2 downto 0);
    signal REGdata: std_logic_vector(31 downto 0);
    signal DESTmux: std_logic;
    signal REGmux2: std_logic;

    signal REGen: std_logic;
    signal REGout1: std_logic_vector(31 downto 0);
    signal REGout2: std_logic_vector(31 downto 0);

    signal SEXTout: std_logic_vector(31 downto 0);

    signal ALU1: std_logic_vector(31 downto 0);
    signal ALU2: std_logic_vector(31 downto 0);
    signal ALUmux1: std_logic;
    signal ALUmux2: std_logic_vector(1 downto 0);

    signal ALUout: std_logic_vector(31 downto 0);
    signal ALUsel: std_logic;
    signal ALUEQ: std_logic;

    signal Vcc: std_logic;

begin
    Vcc <= '1';

    U_PC: reg port map (clk, rst, PCen, ALUresult, PCout);
    U_MA_mux: mux2 port map (PCout, ALUresult, ADDRmux, ADDRout);
    U_RAM: test_ram port map (clk, rst, MEMen, RW, ADDRout, REGout2, RAMout);
    U_IR: reg port map (clk, rst, IRen, RAMout, IRout);
    U_Reg_mux1: mux2r port map (IRout(18 downto 16), IRout(2 downto 0), DESTmux, REGW);
    U_Reg_mux2: mux2 port map (RAMout, ALUresult, REGmux2, REGdata);
    U_RegFile: register_file port map (clk, rst, REGen, REGW, IRout(21 downto 19), IRout(18 downto 16), REGdata, REGout1, REGout2);
    U_SExt: sext port map (IRout(15 downto 0), SEXTout);
    U_ALU_mux1: mux2 port map (PCout, REGout1, ALUmux1, ALU1);
    U_ALU_mux2: mux4 port map (REGout2, SEXTout, ALUmux2, ALU2);
    U_ALU: ALU port map (ALU1, ALU2, ALUsel, ALUout,ALUEQ);
    U_ALUresult: regbuf port map (clk, Vcc, ALUout, ALUresult);
    U_FSM: FSM port map (clk, rst, ALUEQ, IRout(24 downto 22), PCen, ADDRmux, MEMen, RW, IRen, DESTmux, REGmux2, REGen, ALUmux1, ALUsel, ALUmux2);

    outPC <= PCout;
    outMem <= RAMout;
    outIR <= IRout;
    outRF1 <= REGout1;
    outRF2 <= REGout2;
    inALU1 <= ALU1;
    inALU2 <= ALU2;
    outALU <= ALUout;
    outp <= ALUresult;

end bhv;
