describe 'database' do
  before { `rm -rf test.db` }

  def run_script(commands)
    raw_output = nil
    IO.popen('./main test.db', 'r+') do |pipe|
      commands.each { |command| pipe.puts command }

      pipe.close_write

      raw_output = pipe.gets(nil)
    end

    raw_output.split("\n")
  end

  it 'inserts and retrieves a row' do
    result =
      run_script(['insert 1 user1 person1@example.com', 'select', '.exit'])

    expect(result).to match_array(
      [
        'db > Executed.',
        'db > (1, user1, person1@example.com)',
        'Executed.',
        'db > '
      ]
    )
  end

  it 'prints error message when table is full' do
    script = (1..1401).map { |i| "insert #{i} user#{i} person#{i}@example.com" }

    script << '.exit'
    result = run_script(script)
    expect(result[-2]).to eq('db > Error: Table full.')
  end

  it 'allows inserting strings that are the maximum length' do
    long_username = 'a' * 32
    long_email = 'a' * 255

    result =
      run_script(["insert 1 #{long_username} #{long_email}", 'select', '.exit'])

    expect(result).to match_array(
      [
        'db > Executed.',
        "db > (1, #{long_username}, #{long_email})",
        'Executed.',
        'db > '
      ]
    )
  end

  it 'prints error message if strings are too long' do
    too_long_username = 'a' * 33
    too_long_email = 'a' * 256

    result =
      run_script(
        ["insert 1 #{too_long_username} #{too_long_email}", 'select', '.exit']
      )

    expect(result).to match_array(
      ['db > String is too long.', 'db > Executed.', 'db > ']
    )
  end

  it 'prints error message if id is negative' do
    result = run_script(['insert -1 cstack foo@bar.com', 'select', '.exit'])

    expect(result).to match_array(
      ['db > ID must be positive.', 'db > Executed.', 'db > ']
    )
  end

  it 'keeps data after closing connection' do
    result1 = run_script(['insert 1 user1 person1@example.com', '.exit'])

    expect(result1).to match_array(['db > Executed.', 'db > '])

    result2 = run_script(%w[select .exit])

    expect(result2).to match_array(
      ['db > (1, user1, person1@example.com)', 'Executed.', 'db > ']
    )
  end

  it 'prints constants' do
    script = %w[.constants .exit]
    result = run_script(script)

    expect(result).to match_array(
      [
        'db > Constants:',
        'ROW_SIZE: 293',
        'COMMON_NODE_HEADER_SIZE: 6',
        'LEAF_NODE_HEADER_SIZE: 10',
        'LEAF_NODE_CELL_SIZE: 297',
        'LEAF_NODE_SPACE_FOR_CELLS: 4086',
        'LEAF_NODE_MAX_CELLS: 13',
        'db > '
      ]
    )
  end

  it 'allows printing out the structure of a one-node btree' do
    script = [3, 1, 2].map { |i| "insert #{i} user#{i} person#{i}@example.com" }
    script << '.btree'
    script << '.exit'
    result = run_script(script)

    expect(result).to match_array(
      [
        'db > Executed.',
        'db > Executed.',
        'db > Executed.',
        'db > Tree:',
        'leaf (size 3)',
        '  - 0 : 3',
        '  - 1 : 1',
        '  - 2 : 2',
        'db > '
      ]
    )
  end
end
